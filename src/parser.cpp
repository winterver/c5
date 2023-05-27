#include <stdio.h>
#include <stdlib.h>

#include "types.hpp"
#include "image.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "string_pool.hpp"
#include "instructions.hpp"

bool typeinfo::operator==(typeinfo& rhs)
{
	return (type == rhs.type
		&& struct_name == rhs.struct_name
		&& depth == rhs.depth);
}

bool typeinfo::operator!=(typeinfo& rhs)
{
	return !this->operator==(rhs);
}

param* param_set::get(char* name)
{
	auto r = std::find_if(begin(), end(),
		[name] (auto& x) { return name == x.name; });
	return r != end() ? &(*r) : nullptr;
}

bool param_set::operator==(param_set& rhs)
{
	if (size() != rhs.size())
	{
		return false;
	}

	for(int i = 0; i < size(); i++)
	{
		if (at(i).tinfo != rhs[i].tinfo)
		{
			return false;
		}
	}
	return true;
}

bool param_set::operator!=(param_set& rhs)
{
	return !this->operator==(rhs);
}

variable_set::variable_set(variable_set* parent)
	: parent(parent)
{ }

variable* variable_set::get(char* name)
{
	auto r = std::find_if(begin(), end(),
		[name] (auto& x) { return name == x.name; });
	return r != end() ? &(*r) : nullptr;
}

variable* variable_set::search(char* name)
{
	auto r = std::find_if(begin(), end(),
		[name] (auto& x) { return name == x.name; });
	if (r != end())
	{
		return &(*r);
	}
	else
	{
		if (parent != nullptr)
		{
			return parent->search(name);
		}
		return nullptr;
	}
}

function* function_set::get(char* name)
{
	auto r = std::find_if(begin(), end(),
		[name] (auto& x) { return name == x.name; });
	return r != end() ? &(*r) : nullptr;
}

void parser::parse(struct token* tok)
{
	cb.clear();
	gvars.clear();
	funcs.clear();

	this->tok = tok;
	globaloffset = 0;

	// setup entry
	cb.fill(CAL, "main");
	cb.fill(PRTF);
	cb.fill(EXIT);	

	// parsing & code generation
	program();

	// set the operand of the CAL to addr of main()
	char* name = string_pool::get_instance().add("main");
	function* main = funcs.get(name);

	if (main == nullptr)
	{
		error("main() not found");
	}
}

void parser::error(const char* errmsg)
{
	printf("(%d) %s\n", tok->lineno, errmsg);
	exit(-1);
}

void parser::get_variable(char* name, int& addr, int& clazz)
{
	clazz = 0;
	variable* v = curlocal->search(name);
	if (v != nullptr)
	{
		addr = v->addr;
		tinfo = v->tinfo;
		clazz = 1;
	}
	else
	{
		param* p = curfunc->params.get(name);
		if (p != nullptr)
		{
			addr = p->addr;
			tinfo = p->tinfo;
			clazz = 2;
		}
		else
		{
			v = gvars.get(name);
			if (v != nullptr)
			{
				addr = v->addr;
				tinfo = v->tinfo;
				clazz = 3;
			}
		}
	}
}

void parser::access(char* name, int& size)
{
	int addr, clazz;
	// typeinfo stored in tinfo
	get_variable(name, addr, clazz);

	if (clazz == 0)
	{	
		error("unknown variable");
	}
	
	if (tinfo.depth == 0)
	{
		switch(tinfo.type)
		{
		case CHAR: size = 1; break; 
		case SHORT: size = 2; break;
		case INT: size = 4; break; 
		case LONG: size = 8; break;
		default: error("unsupported type"); break;
		}
	}
	else
	{
		size = 8;
	}

	// local variable
	if (clazz == 1)
	{	
		cb.fill(LEA, addr);
	}	
	// parameter
	else if (clazz == 2)
	{	
		cb.fill(LEA, addr+8);
	}
	// global variable
	else if (clazz == 3)
	{	
		cb.fill(GLO, addr);
	}
}

function* parser::get_function(char* name)
{
	auto r = std::find_if(funcs.begin(), funcs.end(),
		[name] (auto& x) { return name == x.name; });
	return r != funcs.end() ? &(*r) : nullptr;
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

void parser::type()
{
	switch(token())
	{
	case VOID:
	case CHAR:
	case SHORT:
	case INT:
	case LONG:
		tinfo.type = token();
		match(tinfo.type);
		tinfo.struct_name = nullptr;
		break;
	case STRUCT:
		tinfo.type = STRUCT;
		match(STRUCT);
		tinfo.struct_name = tok->sval;
		match(IDENTIFIER);
		break;
	default:
		error("a type needed");
	}
}

void parser::depth()
{
	for(tinfo.depth = 0; token() == '*'; tinfo.depth++)
	{
		match('*');
	}
}

void parser::structdef()
{
	match(STRUCT);
	match(IDENTIFIER);
	match('{');
	match('}');
	match(';');
}

void parser::funcdef()
{
	type();
	depth();
	typeinfo ret_type = tinfo;
	char* name = tok->sval;
	match(IDENTIFIER);
	paramlist();

	function func;	
	func.tinfo = tinfo;
	func.name = name;
	func.params = params;
	func.hasbody = false;

	// check if the declaration already exists,
	function* decl = funcs.get(name);

	// if yes, check if both declaration are the same
	if (decl != nullptr)
	{	
		if (decl->tinfo != func.tinfo
			|| decl->params != func.params)
		{
			error("declaration mismatch");
		}
	}

	// if it's a function definition
	if (token() == '{')
	{	
		if (func.hasbody)
		{
			error("function redefinition");
		}
		func.hasbody = true;

		// register/update function info
		if (decl == nullptr)
		{
			funcs.push_back(func);
		}
		else
		{
			*decl = func;
		}
		
		// parse function body
		curfunc = &func;
		curlocal = nullptr;
		localoffset = 0;

		cb.fill(LABL, func.name);
		std::string s = cb.str();
		cb.str(""); // clear() or flush() doesn't work
		
		block();
		std::string s2 = cb.str();
		cb.str("");

		cb << s;
		cb.fill(ADS, localoffset);
		cb << s2;
	}
	else
	{
		// else it's a forward declaration
		match(';');

		if (decl == nullptr)
		{
			funcs.push_back(func);
		}
	}	
}

void parser::gvardef()
{
	type();

NextVar:
	depth();
	char* name = tok->sval;
	match(IDENTIFIER);

	variable var;
	var.tinfo = tinfo;
	var.name = name;	

	if (gvars.get(var.name))
	{
		error("global variable redefinition");
	}
	else
	{
		// alloc memory for the variable in data
		var.addr = globaloffset;
		// TODO support initialization
		// TODO support struct & string & array & float
		if (var.tinfo.depth == 0)
		{
			switch(var.tinfo.type)
			{
			case CHAR: globaloffset += 1; break;
			case SHORT: globaloffset += 2; break; 
			case INT: globaloffset += 4; break;
			case LONG: globaloffset += 8; break;
			default: error("unsupported type"); break;
			}
		}
		else
		{
			globaloffset += 8;
		}
		gvars.push_back(var);
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
	params.clear();

	match('(');

	if (token() == ')')
	{
		match(')');
		return;
	}

	int offset = 0;

NextParam:	
	type();
	depth();
	char* name = tok->sval;
	match(IDENTIFIER);

	param p;
	p.tinfo = tinfo;
	p.name = name;
	p.addr = offset;

	if (p.tinfo.depth == 0)
	{
		switch(p.tinfo.type)
		{
		case CHAR: offset += 1; break;
		case SHORT: offset += 2; break;
		case INT: offset += 4; break;
		case LONG: offset += 8; break;
		default: error("unsupported type"); break;
		}
	}
	else
	{
		offset += 8;
	}

	if (params.get(p.name))
	{
		error("param redefinition");
	}
	params.push_back(p);

	if (token() == ',')
	{
		match(',');
		goto NextParam;
	}

	match(')');
}

void parser::block()
{
	match('{');

	variable_set local(curlocal);
	curlocal = &local;

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
			block();
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
				call(cb);
			}
			else
			{
				// assignment
				assign();
				match(';');
			}
		}
		else if (token() == RETURN)
		{
			match(RETURN);
			if (token() == ';')
			{
				// return without a value
				match(';');
			}
			else
			{
				// return with a value
				expression(cb);
				match(';');
			}
			cb.fill(RET);
		}
		else
		{
			// local variable definition
			lvardef();
		}
	}

	cb.fill(RET);
	
	curlocal = curlocal->parent;
	match('}');
}

void parser::lvardef()
{
	type();

NextVar:
	depth();
	char* name = tok->sval;
	match(IDENTIFIER);

	variable var;
	var.tinfo = tinfo;
	var.name = name;	

	if (curlocal->get(var.name))
	{
		error("local variable redefinition");
	}
	else
	{
		// alloc memory for the variable in data
		var.addr = localoffset;
		// TODO support initialization
		// TODO support struct & string & array & float
		if (var.tinfo.depth == 0)
		{
			switch(var.tinfo.type)
			{
			case CHAR: localoffset -= 1; break;
			case SHORT: localoffset -= 2; break;
			case INT: localoffset -= 4; break;
			case LONG: localoffset -= 8; break;
			default: error("unsupported type"); break;
			}
		}
		else
		{
			localoffset -= 8;
		}
		curlocal->push_back(var);
	}
	
	if (token() == ',')
	{
		match(',');	
		goto NextVar;	
	}
	match(';');
}

void parser::assign()
{
	char* name = tok->sval;
	match(IDENTIFIER);
	match('=');

	expression(cb);
	cb.fill(PUQ);
	
	int size;
	access(name, size);

	switch(size)
	{	
	case 1:	cb.fill(STB); break;
	case 2:	cb.fill(STW); break;
	case 4:	cb.fill(STD); break;
	case 8:	cb.fill(STQ); break;
	}
}

void parser::call(codebuf& buf)
{
	char* name = tok->sval;
	match(IDENTIFIER);

	curfunc = get_function(name);
	if (curfunc == nullptr)
	{
		error("function not found");
	}	
	
	npassed = 0;
	call_stack_size = 0;
	match('('); // for the sake of recursion
	arglist(buf);
	match(')');

	if (npassed < curfunc->params.size())
	{
		error("too few arguments");
	}	

	buf.fill(CAL, curfunc->name);
	buf.fill(ADS, call_stack_size);	
}

void parser::arglist(codebuf& _buf)
{
	if (token() == ')')
	{
		return;
	}

	codebuf buf;
	expression(buf);

	if (npassed >= curfunc->params.size())
	{
		error("too many arguments");
	}

	param p = curfunc->params[npassed];
	switch(p.tinfo.type)
	{
	case CHAR: buf.fill(PUB); call_stack_size += 1; break;
	case SHORT: buf.fill(PUW); call_stack_size += 2; break;
	case INT: buf.fill(PUD); call_stack_size += 4; break;
	case LONG: buf.fill(PUQ); call_stack_size += 8; break;
	}

	npassed++;

	if (token() == ',')
	{
		match(',');
		arglist(_buf);
	}

	_buf << buf.str();
}

void parser::expression(codebuf& buf)
{
	term1(buf);
	while (token() == '<' 
		|| token() == '>'
		|| token() == LESS_EQUAL
		|| token() == GREATER_EQUAL)
	{
		int t = token();
		match(t);
		buf.fill(PUQ);
		term1(buf);

        switch(t)
		{
		case '<': buf.fill(LT); break;
		case '>': buf.fill(GT); break;
		case LESS_EQUAL: buf.fill(LE); break;
		case GREATER_EQUAL: buf.fill(GE); break;
		}
    }	
}

void parser::term1(codebuf& buf)
{
	term2(buf);
	while (token() == '+' || token() == '-')
	{
		int t = token();
		match(t);
		buf.fill(PUQ);
		term2(buf);

        switch(t)
		{
		case '+': buf.fill(ADD); break;
		case '-': buf.fill(SUB); break;
		}
    }
}

void parser::term2(codebuf& buf)
{
	factor(buf);
	while (token() == '*' || token() == '/' || token() == '%')
	{
		int t = token();
		match(t);
		buf.fill(PUQ);
		factor(buf);

        switch(t)
		{
		case '*': buf.fill(MUL); break;
		case '/': buf.fill(DIV); break;
		case '%': buf.fill(MOD); break;
		}
    }
}

void parser::factor(codebuf& buf)
{
	if (token() == '(') {
        match('(');
        expression(buf);
        match(')');
	}
	else if (token() == '-')
	{
		match('-');
		expression(buf);
		buf.fill(NEG);
	}
	else if (token() == '&')
	{
		match('&');
		char* name = tok->sval;
		match(IDENTIFIER);

		int size;
		access(name, size);
	}
	else if (token() == IDENTIFIER)
	{
		struct token* prev = tok;
		match(IDENTIFIER);
		int t = token();
		tok = prev;

		if (t == '(')
		{
			function* bak_curfunc = curfunc;
			int bak_npassed = npassed;
			int bak_call_stack_size = call_stack_size;
			call(buf);
			npassed = bak_npassed;
			call_stack_size = bak_call_stack_size;
			curfunc = bak_curfunc;
		}
		else
		{
			// variable access
			char* name = tok->sval;
			match(IDENTIFIER);

			int size; // the size of the value pointed by acc
			access(name, size); // address of the variable is now in acc
			switch(size)
			{
			case 1: buf.fill(LOB); break;
			case 2: buf.fill(LOW); break;
			case 4: buf.fill(LOD); break;
			case 8: buf.fill(LOQ); break;
			}
		}
	}
	else if (token() == NUMBER)
	{
		auto num = tok->ival;
		match(NUMBER);
		buf.fill(IMQ, i64(num));
	}
	else
	{
		error("unexpected expression");
	}
}
