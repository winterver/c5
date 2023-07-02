%include {

#include <stdio.h>
#include <string.h>
#include <vector>
#include "symtab.hpp"
#include "semantics.hpp"

#define ZERO(s) memset(&s, 0, sizeof(s))
void yyerror(const char* s);

// states of the parser
int localoffset = 0;
int globaloffset = 0;

struct decl_specif_t {
	int type; 
};

struct init_decl_t {
	int depth;
	const char* name;
};

struct func_decl_t {
	int depth;
	const char* name;
	int nparams;
	param_t* params;
	bool variadic;
};

// helper function
template<class T>
T* extract(std::vector<T>* vec)
{
	auto res = new T[vec->size()];
	std::copy(vec->begin(), vec->end(), res);
	return res;
}

int get_size(int type, int depth)
{
	if (depth)
		return 8;
	switch(type)
	{
	case TYPE_CHAR: return 1;
	case TYPE_SHORT: return 2;
	case TYPE_INT: return 4;
	case TYPE_LONG: return 8;
	case TYPE_VOID: return 0;
	}
	yyerror("illegal type");
	return 0;
}

} // end of %include

%token NUM DEC ID STR.
%token ASGN_OP LT_OP GT_OP ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP.
%token AND_OP OR_OP XOR_OP NOT_OP LOGAND LOGOR LOGNOT.
%token DOT_OP PTR_OP INC_OP DEC_OP SHL_OP SHR_OP LE_OP GE_OP EQ_OP NE_OP.
%token MULASGN DIVASGN MODASGN ADDASGN SUBASGN.
%token SHLASGN SHRASGN ANDASGN XORASGN ORASGN.

%token SIZEOF ELLIPSIS.
%token TYPEDEF STATIC CONST.
%token VOID CHAR SHORT INT LONG FLOAT DOUBLE TYPE.
%token IF ELSE FOR WHILE DO CONTINUE BREAK RETURN GOTO.

//     (  )  [  ]  {  }  ,   ;   :   ?
%token LP RP LS RS LB RB COM SEM COL QUE.

%token_type { token_value_t }
%type declaration_specifiers { decl_specif_t }
%type type_specifier { decl_specif_t }
%type pointer { int }
%type direct_declarator { init_decl_t }
%type declarator { init_decl_t }
%type init_declarator { init_decl_t }
%type init_declarator_list { std::vector<init_decl_t>* }
%type parameter_declaration { param_t }
%type parameter_list { std::vector<param_t>* }
%type function_declarator { func_decl_t }

%type expression { expr_t* }
%type primary_expression { expr_t* }

%destructor init_declarator_list { delete $$; }
%destructor parameter_list { delete $$; }

%syntax_error { yyerror("syntax error"); }

%start_symbol start
start ::= .
start ::= translation_unit.

primary_expression(R) ::= ID(A). {
	R = new expr_t;
	R->category = CATEGORY_VARREF;
	R->left = true;

	auto sym = lookup(A.sval);
	R->type = sym->type;
	R->depth = sym->depth;
	R->varref = sym;
}
primary_expression(R) ::= NUM(A). {
	R = new expr_t;
	R->category = CATEGORY_LITERAL;
	R->left = false;

	R->type = A.type;
	R->depth = 0;
	R->ival = A.ival;
}
primary_expression(R) ::= DEC(A). {
	R = new expr_t;
	R->category = CATEGORY_LITERAL;
	R->left = false;

	R->type = A.type;
	R->depth = 0;
	R->fval = A.fval;
}
primary_expression(R) ::= STR(A). {
	R = new expr_t;
	R->category = CATEGORY_LITERAL;
	R->left = false;

	R->type = TYPE_CHAR;
	R->depth = 1;
	R->sval = A.sval;
}
primary_expression(R) ::= LP expression RP. { /*TODO*/ }

postfix_expression ::= primary_expression.
postfix_expression ::= postfix_expression LS expression RS.
postfix_expression ::= postfix_expression LP RP.
postfix_expression ::= postfix_expression LP argument_expression_list RP.
postfix_expression ::= postfix_expression INC_OP.
postfix_expression ::= postfix_expression DEC_OP.

argument_expression_list ::= assignment_expression.
argument_expression_list ::= argument_expression_list COM assignment_expression.

unary_expression ::= postfix_expression.
unary_expression ::= INC_OP unary_expression.
unary_expression ::= DEC_OP unary_expression.
unary_expression ::= unary_operator cast_expression.
unary_expression ::= SIZEOF unary_expression.
unary_expression ::= SIZEOF LP type_name RP.

unary_operator ::= AND_OP.
unary_operator ::= MUL_OP.
unary_operator ::= ADD_OP.
unary_operator ::= SUB_OP.
unary_operator ::= NOT_OP.
unary_operator ::= LOGNOT.

cast_expression ::= unary_expression.
cast_expression ::= LP type_name RP cast_expression.

multiplicative_expression ::= cast_expression.
multiplicative_expression ::= multiplicative_expression MUL_OP cast_expression.
multiplicative_expression ::= multiplicative_expression DIV_OP cast_expression.
multiplicative_expression ::= multiplicative_expression MOD_OP cast_expression.

additive_expression ::= multiplicative_expression.
additive_expression ::= additive_expression ADD_OP multiplicative_expression.
additive_expression ::= additive_expression SUB_OP multiplicative_expression.

shift_expression ::= additive_expression.
shift_expression ::= shift_expression SHL_OP additive_expression.
shift_expression ::= shift_expression SHR_OP additive_expression.

relational_expression ::= shift_expression.
relational_expression ::= relational_expression LT_OP shift_expression.
relational_expression ::= relational_expression GT_OP shift_expression.
relational_expression ::= relational_expression LE_OP shift_expression.
relational_expression ::= relational_expression GE_OP shift_expression.

equality_expression ::= relational_expression.
equality_expression ::= equality_expression EQ_OP relational_expression.
equality_expression ::= equality_expression NE_OP relational_expression.

and_expression ::= equality_expression.
and_expression ::= and_expression AND_OP equality_expression.

exclusive_or_expression ::= and_expression.
exclusive_or_expression ::= exclusive_or_expression OR_OP and_expression.

inclusive_or_expression ::= exclusive_or_expression.
inclusive_or_expression ::= inclusive_or_expression XOR_OP exclusive_or_expression.

logical_and_expression ::= inclusive_or_expression.
logical_and_expression ::= logical_and_expression LOGAND inclusive_or_expression.

logical_or_expression ::= logical_and_expression.
logical_or_expression ::= logical_or_expression LOGOR logical_and_expression.

conditional_expression ::= logical_or_expression.
conditional_expression ::= logical_or_expression QUE expression COL conditional_expression.

assignment_expression ::= conditional_expression.
assignment_expression ::= unary_expression assignment_operator assignment_expression.

assignment_operator ::= ASGN_OP.
assignment_operator ::= MULASGN.
assignment_operator ::= DIVASGN.
assignment_operator ::= MODASGN.
assignment_operator ::= ADDASGN.
assignment_operator ::= SUBASGN.
assignment_operator ::= SHLASGN.
assignment_operator ::= SHRASGN.
assignment_operator ::= ANDASGN.
assignment_operator ::= XORASGN.
assignment_operator ::= ORASGN.

expression ::= assignment_expression.
expression ::= expression COM assignment_expression.

variable_declaration ::= declaration_specifiers(A) init_declarator_list(B) SEM. {
	for (auto& idl : *B)
	{
		sym_t* var = insert(idl.name);
		var->type = A.type;
		var->depth = idl.depth;
		if (var->type == TYPE_VOID && var->depth == 0)
		{
			yyerror("illegal type");
		}
		
		if (var->scope == 0)
		{
			var->category = CATEGORY_GLOBAL;
			var->offset = globaloffset;
			globaloffset += get_size(var->type, var->depth);
		}
		else
		{
			var->category = CATEGORY_LOCAL;
			// stack grows downward
			localoffset -= get_size(var->type, var->depth);
			var->offset = localoffset;
		}
	}
}

declaration_specifiers(R) ::= type_specifier(A). { R = A; }

init_declarator_list(R) ::= init_declarator(A). {
	R = new std::vector<init_decl_t>;
	R->push_back(A);
}
init_declarator_list(R) ::= init_declarator_list(A) COM init_declarator(B). {
	A->push_back(B);
	R = A;
}

init_declarator(R) ::= declarator(A). { R = A; }
init_declarator ::= declarator ASGN_OP initializer. {
	yyerror("initializer is currently not supported");
}

type_specifier(R) ::= VOID. { ZERO(R); R.type = TYPE_VOID; }
type_specifier(R) ::= CHAR. { ZERO(R); R.type = TYPE_CHAR; }
type_specifier(R) ::= SHORT. { ZERO(R); R.type = TYPE_SHORT; }
type_specifier(R) ::= INT. { ZERO(R); R.type = TYPE_INT; }
type_specifier(R) ::= LONG. { ZERO(R); R.type = TYPE_LONG; }

declarator(R) ::= pointer(A) direct_declarator(B). { B.depth = A; R = B; }
declarator(R) ::= direct_declarator(A). { R = A; }

direct_declarator(R) ::= ID(A). { ZERO(R); R.name = A.sval; }

pointer(R) ::= MUL_OP. { R = 1; }
pointer(R) ::= MUL_OP pointer(A). { R = A + 1; }

parameter_list(R) ::= parameter_declaration(A). {
	R = new std::vector<param_t>;
	R->push_back(A);
}
parameter_list(R) ::= parameter_list(A) COM parameter_declaration(B). {
	A->push_back(B);
	R = A;
}

parameter_declaration(R) ::= declaration_specifiers(A) declarator(B). { 
	ZERO(R);
	R.type = A.type; 
	R.depth = B.depth;
	R.name = B.name;
}

type_name ::= declaration_specifiers.
type_name ::= declaration_specifiers pointer.

initializer ::= assignment_expression.

statement ::= labeled_statement.
statement ::= compound_statement.
statement ::= expression_statement.
statement ::= selection_statement.
statement ::= iteration_statement.
statement ::= jump_statement.

labeled_statement ::= ID COL statement.

compound_statement ::= LB RB.
compound_statement ::= LB block_item_list RB.

block_item_list ::= block_item.
block_item_list ::= block_item_list block_item.

block_item ::= variable_declaration.
block_item ::= statement.

expression_statement ::= SEM.
expression_statement ::= expression SEM.

selection_statement ::= IF LP expression RP statement.
selection_statement ::= IF LP expression RP statement ELSE statement.

iteration_statement ::= WHILE LP expression RP statement.
iteration_statement ::= DO statement WHILE LP expression RP SEM.
iteration_statement ::= FOR LP expression_statement expression_statement RP statement.
iteration_statement ::= FOR LP expression_statement expression_statement expression RP statement.
iteration_statement ::= FOR LP variable_declaration expression_statement RP statement.
iteration_statement ::= FOR LP variable_declaration expression_statement expression RP statement.

jump_statement ::= GOTO ID SEM.
jump_statement ::= CONTINUE SEM.
jump_statement ::= BREAK SEM.
jump_statement ::= RETURN SEM.
jump_statement ::= RETURN expression SEM.

translation_unit ::= external_declaration.
translation_unit ::= translation_unit external_declaration.

external_declaration ::= variable_declaration.
external_declaration ::= function_definition.

function_declarator(R) ::= declarator(A) LP RP. {
	ZERO(R);
	R.depth = A.depth;
	R.name = A.name;
}

function_declarator(R) ::= declarator(A) LP parameter_list(B) RP. {
	ZERO(R);
	R.depth = A.depth;
	R.name = A.name;
	R.nparams = B->size();
	R.params = extract(B);
}
function_declarator(R) ::= declarator(A) LP parameter_list(B) COM ELLIPSIS RP. {
	ZERO(R);
	R.depth = A.depth;
	R.name = A.name;
	R.nparams = B->size();
	R.params = extract(B);
	R.variadic = true;
}

function_signature ::= declaration_specifiers(A) function_declarator(B). {
	if (lookup(B.name))
	{
		yyerror("function name conflict");
	}

	sym_t* func = insert(B.name);
	func->category = CATEGORY_FUNC;
	func->type = A.type;
	func->depth = B.depth;
	func->name = B.name;
	func->nparams = B.nparams;
	func->params = B.params;
	func->variadic = B.variadic;

	next_scope();

	int paramoffset = 8; // bp, retaddr
	for(int i = 0; i < func->nparams; i++)
	{
		param_t p = func->params[i];
		sym_t* param = insert(p.name);

		param->category = CATEGORY_PARAM;
		param->offset = paramoffset;
		paramoffset += get_size(p.type, p.depth);
	
		param->type = p.type;
		param->depth = p.depth;

		if (param->type == TYPE_VOID && param->depth == 0)
		{
			yyerror("illegal type");
		}
	}

	prev_scope();
}

function_definition ::= function_signature compound_statement. {
	exit_scope();

	// A->stmts = B;
	// A->local_stack_size = -localoffset;
	// localoffset = 0;
}

%code {

#include <malloc.h>

int yylex(void);
// defined in lexer.l
extern token_value_t yylval;

int main()
{
	void* par = ParseAlloc(malloc);
	ParseInit(par);

	int token;
	while((token = yylex()) > 0)
	{
		Parse(par, token, yylval);
	}

	Parse(par, 0, yylval);
	ParseFree(par, free);
}

}
