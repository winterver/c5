#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include "parser.hpp"
#include "string_pool.hpp"

void parser::parse(struct token* tok)
{
	this->tok = tok;

	// parsing & code generation
	program();
}

void parser::error(const char* errmsg)
{
	printf("(%d) %s\n", tok->lineno, errmsg);
	exit(-1);
}

Variable* parser::find_variable(char* name)
{
	auto find = [](List<Variable*>& vars, char* name)
	{
		auto it = std::find_if(
			vars.begin(), 
			vars.end(), 
			[name](auto lhs)
			{
				return lhs->name == name;
			}
		);
		return it != vars.end() ? (*it) : nullptr;
	};

	// search block tree
	for(Block* blk = curblk; blk != nullptr; blk = blk->parent)
	{
		Variable* var = find(blk->locals, name);
		if (var != nullptr)
		{
			return var;
		}
	}

	// search parameters
	if (cursig != nullptr)
	{
		Variable* var = find(cursig->params, name);
		if (var != nullptr)
		{
			return var;
		}
	}

	// search globals
	return find(globals, name);
}

Function* parser::find_function(char* name)
{
	auto it = std::find_if(
		functions.begin(), 
		functions.end(), 
		[name](auto lhs)
		{
			return lhs->sig->name == name;
		}
	);
	return it != functions.end() ? (*it) : nullptr;
}

int parser::token()
{
	return tok->tok;
}

void parser::match(int t)
{
	if (t == token())
	{
		tok++;
	}
	else
	{
		printf("required: %d provided: %d\n", t, token());
		error("token mismatch");
	}
}

void parser::program()
{
	while(token())
	{
		struct token* prev = tok;
		type();
		depth();
		match(IDENTIFIER);
		int next = token();
		tok = prev;

		if (next == '{')
		{
			structdef();
		}
		else if (next == '(')
		{
			funcdef();
		}
		else
		{
			gvardef();
		}	
	}
}

Type parser::type()
{
	Type t;

	switch(token())
	{
	case VOID:
	case CHAR:
	case SHORT:
	case INT:
	case LONG:
		t.id = token();
		match(t.id);
		break;
	case STRUCT:
		error("struct is currently not supported.");
		break;
	default:
		error("a type needed");
	}

	return t;
}

int parser::depth()
{
	int dep;
	for(dep = 0; token() == '*'; dep++)
	{
		match('*');
	}
	return dep;
}

void parser::structdef()
{
	error("struct is currently not supported.");
}

void parser::funcdef()
{
	Type type = this->type();
	type.depth = this->depth();

	char* name = tok->sval;
	match(IDENTIFIER);

	auto it = std::find_if(
		functions.begin(), 
		functions.end(), 
		[name](auto& lhs) {
			return lhs->sig->name == name;
		}
	);

	Signature* sig = new Signature(type, name);
	cursig = sig;
	paramlist();
	
	// TODO
	// check if the declaration already exists,
	// if yes, check if both declaration are the same	

	Block* body = nullptr;
	body = block();

	if (it == functions.end())
	{
		functions.push_back(new Function(sig, body));
	}
	else
	{
		error("function redefinition");
	}

	cursig = nullptr;
}

void parser::gvardef()
{
	Type type = this->type();
NextVar:
	type.depth = this->depth();
	char* name = tok->sval;
	match(IDENTIFIER);

	auto it = std::find_if(
		globals.begin(), 
		globals.end(), 
		[name](auto& lhs) {
			return lhs->name == name;
		}
	);

	if (it == globals.end())
	{
		globals.push_back(new Variable(type, name));
	}
	else
	{
		error("global variable redefinition");
	}
	
	if (token() == ',')
	{
		match(',');	
		goto NextVar;	
	}
	match(';');
}

void parser::paramlist()
{
	match('(');

	if (token() == ')')
	{
		match(')');
		return;
	}

NextParam:	
	Type type = this->type();
	type.depth = this->depth();

	char* name = tok->sval;
	match(IDENTIFIER);

	auto it = std::find_if(
		cursig->params.begin(), 
		cursig->params.end(), 
		[name](auto lhs) {
			return lhs->name == name;
		}
	);
	
	if (it == cursig->params.end())
	{
		cursig->params.push_back(new Variable(type, name));
	}
	else
	{
		error("parameter redefinition");
	}

	if (token() == ',')
	{
		match(',');
		goto NextParam;
	}

	match(')');
}

Block* parser::block()
{
	Block* blk = new Block;
	blk->parent = curblk;
	curblk = blk;

	match('{');

	while(token() != '}')
	{
		if (token() == ';')
		{
			// empty statement
			match(';');
		}
		else if (token() == '{')
		{
			// anonymous block
			blk->stmts.push_back(block());
		}
		else if (token() == IDENTIFIER)
		{
			struct token* prev = tok;
			match(IDENTIFIER);
			int next = token();
			tok = prev;

			if (next == '(')
			{
				// function call
				blk->stmts.push_back(call());
			}
			else
			{
				// assignment
				blk->stmts.push_back(assign());
			}
			match(';');
		}
		else if (token() == RETURN)
		{
			ReturnStmt* ret = new ReturnStmt;

			match(RETURN);
			if (token() == ';')
			{
				// return without a value
				match(';');
			}
			else
			{
				// return with a value
				ret->expr = expression();
				match(';');
			}

			blk->stmts.push_back(ret);
		}
		else
		{
			// local variable definition
			lvardef();
		}
	}

	match('}');

	curblk = blk->parent;
	return blk;
}

void parser::lvardef()
{
	Type type = this->type();
NextVar:
	type.depth = this ->depth();

	struct token* bak = tok;
	
	char* name = tok->sval;
	match(IDENTIFIER);

	auto it = std::find_if(
		curblk->locals.begin(), 
		curblk->locals.end(), 
		[name](auto& lhs) {
			return lhs->name == name;
		}
	);

	if (it == curblk->locals.end())
	{
		curblk->locals.push_back(new Variable(type, name));
	}
	else
	{
		error("local variable redefinition");
	}

	if (token() == '=')
	{
		tok = bak;
		curblk->stmts.push_back(assign());
	}
	
	if (token() == ',')
	{
		match(',');	
		goto NextVar;	
	}
	match(';');
}

Assignment* parser::assign()
{
	Assignment* assignment = new Assignment;

	char* name = tok->sval;
	match(IDENTIFIER);
	match('=');

	Variable* var = find_variable(name);
	if (var == nullptr)
	{
		error("undefined variable");
	}

	assignment->left = new LeftExpression(var);
	assignment->right = expression();
	return assignment;
}

CallStmt* parser::call()
{
	char* name = tok->sval;
	match(IDENTIFIER);

	Function* func = find_function(name);
	if (func == nullptr)
	{
		error("undefined function");
	}
	
	List<Expression*> args;
	arglist(func, args);

	return new CallStmt(func, args);
}

void parser::arglist(Function* func, List<Expression*>& args)
{
	match('(');
	if (token() == ')')
	{
		match(')');
		return;
	}

NextArg:
	args.push_back(expression());
	// TODO: type check

	if (token() == ',')
	{
		match(',');
		goto NextArg;
	}
	match(')');
}

Expression* parser::expression()
{
	return term1();
}

LeftExpression* parser::left_expression()
{
	char* name = tok->sval;
	match(IDENTIFIER);

	Variable* var = find_variable(name);
	if (var == nullptr)
	{
		error("undefined variable");
	}
	return new LeftExpression(var);
}

Expression* parser::term1()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term2();
	while (token() == LOGIC_OR)
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term2()));
	}

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term2()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term3();
	while (token() == LOGIC_AND)
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term3()));
	}

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term3()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term4();
	while (token() == '|')
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term4()));
	}

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term4()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term5();
	while (token() == '^')
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term5()));
	}

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term5()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term6();
	while (token() == '&')
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term6()));
	}

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term6()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term7();
	while (token() == EQUAL || token() == NOT_EQUAL)
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term7()));
    }
	
	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term7()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term8();
	while (token() == '<' 
		|| token() == '>'
		|| token() == LESS_EQUAL
		|| token() == GREATER_EQUAL)
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term8()));
    }	

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term8()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term9();
	while (token() == LSHIFT || token() == RSHIFT)
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term9()));
    }

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term9()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = term10();
	while (token() == '+' || token() == '-')
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, term10()));
    }

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::term10()
{
	ChainedExpression* cexp = nullptr;
	cexp = new ChainedExpression;

	cexp->lhs = factor();
	while (token() == '*' || token() == '/' || token() == '%')
	{
		int tk = token();
		match(tk);
		cexp->rhs.push_back(
			std::make_pair(tk, factor()));
    }

	if (cexp->rhs.empty())
	{
		auto lhs = cexp->lhs;
		delete cexp;
		return lhs;
	}
	else
	{
		return cexp;
	}
}

Expression* parser::factor()
{
	Expression* result = nullptr;

	if (token() == '(') {
        match('(');
        result = expression();
        match(')');
	}
	else if (token() == '-')
	{
		match('-');
		result = new UnaryExpression('-', expression());
	}
	else if (token() == '~')
	{
		match('~');
		result = new UnaryExpression('~', expression());
	}
	else if (token() == '&')
	{
		match('&');
		result = new UnaryExpression('&', expression());
	}
	else if (token() == '*')
	{
		match('*');
		result = new UnaryExpression('*', expression());
	}
	else if (token() == NUMBER)
	{
		long long ival = tok->ival;
		match(NUMBER);
		result = new IntegerLiteral(ival);
	}
	else if (token() == DECIMAL)
	{
		long double fval = tok->fval;
		match(DECIMAL);
		result = new DecimalLiteral(fval);
	}
	else if (token() == STRING)
	{
		char* sval = tok->sval;
		match(STRING);
		result = new StringLiteral(sval);
	}
	else
	{
		result = left_expression();
	}

	return result;
}
