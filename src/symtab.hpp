#pragma once
#include <vector>

// categories for symbols
#define CATEGORY_GLOBAL 1
#define CATEGORY_FUNC 2
#define CATEGORY_PARAM 3
#define CATEGORY_LOCAL 4
#define CATEGORY_LABEL 5

// categories for expressions
#define CATEGORY_COMBINED 1
#define CATEGORY_LITERAL 2
#define CATEGORY_VARREF 3

// operators
#define OP_REF 1
#define OP_DEREF 2
#define OP_NEG 3
#define OP_NOT 4
#define OP_LOGNOT 5
#define OP_PRE_INC 6
#define OP_PRE_DEC 7
#define OP_POST_INC 8
#define OP_POST_DEC 9
#define OP_CAST 10
#define OP_ASGN 11
#define OP_ADD 12
#define OP_SUB 13
#define OP_MUL 14
#define OP_DIV 15
#define OP_MOD 16
#define OP_AND 17
#define OP_OR 18
#define OP_XOR 19
#define OP_LOGAND 20
#define OP_LOGOR 21
#define OP_EQ 22
#define OP_NE 23
#define OP_LT 24
#define OP_GT 25
#define OP_LE 26
#define OP_GE 27
#define OP_SHL 28
#define OP_SHR 29

struct sym_t;

struct expr_t
{
	int type; // data type of the expression
	int depth;

	int op;
	expr_t* lhs;
	expr_t* rhs;

	int category;
	bool left; // true -> lvalue, false -> rvalue
	union {
		long long ival;
		long double fval;
		const char* sval;
		sym_t* varref;
	};
};

struct param_t
{
	int type;
	int depth;
	const char* name;
};

typedef std::vector<param_t> param_list_t;

struct stmt_t
{
	int category;
	std::vector<stmt_t>* compound;
};

typedef std::vector<stmt_t> stmt_list_t;

struct sym_t
{
	sym_t* next;
	int scope;

	int category;
	int offset;

	int type;
	int depth;
	const char* name;
	
	param_list_t* params;
	bool variadic;
	int localsize; // size of local variables
};

sym_t* insert(const char* name);
sym_t* lookup(const char* name);
sym_t* lookup_type(const char* name);

void next_scope();
void prev_scope();
void exit_scope();
