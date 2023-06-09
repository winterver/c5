#pragma once
#include <vector>
#include <typeinfo>
#include <stdio.h>

template<class T>
using List = std::vector<T>;

struct Type
{
	int id; // CHAR SHORT INT LONG or STRUCT
	//structinfo sinfo; // valid only if id = STRUCT
	int depth; // non-zero indicates pointer
	//int dims; // dimentions
	//int* len; // length of each dimension
	
	Type() : id(0), depth(0) { }
};

struct Variable
{
	const Type type;
	const char* const name;
	Variable(const Type& type, char* name)
		: type(type), name(name) { }
};

struct Statement
{
	virtual void dummy() { }
	virtual void print(int indent) = 0;
};

struct Expression : Statement { };

#define TABSIZE 2

// expression chained with operators
struct ChainedExpression : Expression
{
	Expression* lhs;
	List<std::pair<int, Expression*>> rhs;

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s\n", typeid(*this).name());
		lhs->print(indent+1);
		for(auto p : rhs)
		{	
			printf("%*s", (indent+1)*TABSIZE, "");
			printf("Operator %c\n", p.first);
			p.second->print(indent+1);
		}
	}
};

struct Factor : Expression { };

struct IntegerLiteral : Factor
{
	const long long value;
	IntegerLiteral(long long val) : value(val) { }

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s ", typeid(*this).name());
		printf("%lld\n", value);
	}
};

struct DecimalLiteral : Factor
{
	const long double value;
	DecimalLiteral(long double val) : value(val) { }

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s ", typeid(*this).name());
		printf("%Lf\n", value);
	}
};

struct StringLiteral : Factor
{
	const char* const value;
	StringLiteral(const char* val) : value(val) { };

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s ", typeid(*this).name());
		printf("\"%s\"\n", value);
	}
};

// complex lvalue expression is currently not supported.
struct LeftExpression : Factor
{
	Variable* var;
	LeftExpression(Variable* var) : var(var) { }

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s ", typeid(*this).name());
		printf("%s\n", var->name);
	}
};

// expression preceeded by an unary operator
struct UnaryExpression : Factor
{
	int op;
	Expression* expr;

	UnaryExpression(int op, Expression* expr)
		: op(op), expr(expr) { }

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s\n", typeid(*this).name());
		printf("Operator %c\n", op);
		expr->print(indent+1);
	}
};

struct Assignment : Statement
{
	LeftExpression* left;
	Expression* right;

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s\n", typeid(*this).name());
		left->print(indent+1);
		right->print(indent+1);
	}
};

struct Function;

struct CallStmt : Statement
{
	Function* func;
	List<Expression*> args;

	CallStmt(Function* func, List<Expression*>& args)
		: func(func), args(args) { }

	void print(int indent);	
};

struct ReturnStmt : Statement
{
	Expression* expr = nullptr;

	void print(int indent)
	{
		printf("%*s", indent*TABSIZE, "");
		printf("%s\n", typeid(*this).name());
		expr->print(indent+1);
	}
};

struct Block : Statement
{
	Block* parent = nullptr;
	List<Variable*> locals;
	List<Statement*> stmts;

	void print(int indent)
	{
		for(auto var : locals)
		{
			printf("%*s", indent*TABSIZE, "");
			printf("Local %s\n", var->name);	
		}
		for(auto stmt : stmts)
		{
			stmt->print(indent);
		}
	}
};

struct Signature
{
	const Type type; // return type
	const char* const name;
	List<Variable*> params;

	Signature(const Type& type,
		const char* const name)
	: type(type), name(name) { }
};

struct Function
{
	Signature* sig;
	Block* body;

	Function(Signature* sig, Block* body)
	: sig(sig), body(body) { }
};

inline void CallStmt::print(int indent)
{
	printf("%*s", indent*TABSIZE, "");
	printf("%s %s\n", typeid(*this).name(), func->sig->name);
	for(auto expr : args)
	{
		expr->print(indent+1);
	}
}
