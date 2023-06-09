#pragma once
#include <vector>
#include <sstream>
#include "ast.hpp"

// tokens
enum {
	// types
	VOID = 256,
	CHAR, 
	SHORT, 
	INT, 
	LONG, 
	FLOAT, 
	DOUBLE, 
	// keywords
	STRUCT,
	RETURN,
	// identifier & literals
	IDENTIFIER, 
	NUMBER, 
	STRING, 
	DECIMAL,
	// multi-character operators
	EQUAL,
	NOT_EQUAL,
	GREATER_EQUAL,
	LESS_EQUAL,
	PLUS_ASSIGN,
	MINUS_ASSIGN,
	MUL_ASSIGN,
	DIV_ASSIGN,
	MOD_ASSIGN,
	AND_ASSIGN,
	OR_ASSIGN,
	NOT_ASSIGN,
	LOGIC_AND,
	LOGIC_OR,
	LSHIFT,
	RSHIFT,
	LSHIFT_ASSIGN,
	RSHIFT_ASSIGN,
	INCREASE,
	DECREASE,
	ARROW,
	ELLIPSIS,
};

struct token
{
	int tok;
	int lineno;
	union {
		long long int ival;
		long double fval;
		char* sval;
	};
};

class parser
{
public:
	void parse(struct token* tok);

public:
	List<Variable*> globals;
	List<Function*> functions;
	Block* curblk = nullptr;
	Signature* cursig = nullptr;

	Variable* find_variable(char* name);
	Function* find_function(char* name);
	void error(const char* errmsg);

private:
	struct token* tok;

	int token();
	void match(int t);

	void program();
	Type type();
	int depth();
	void structdef();
	void gvardef();
	void funcdef();
	void paramlist();
	Block* block();
	void lvardef();
	Assignment* assign();
	CallStmt* call();
	void arglist(Function* func, List<Expression*>& args);

	LeftExpression* left_expression();
	Expression* expression();
	Expression* term1();
	Expression* term2();
	Expression* term3();
	Expression* term4();
	Expression* term5();
	Expression* term6();
	Expression* term7();
	Expression* term8();
	Expression* term9();
	Expression* term10();
	Expression* factor();
};
