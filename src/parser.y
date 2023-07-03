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
	int depth; // only used by type_name
};

struct init_decl_t {
	int depth;
	const char* name;
	expr_t* init;
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

bool convertible(expr_t* B, decl_specif_t A)
{
	if (B->depth != A.depth)
		return false;
	return true;
}

int hybrid(int t1, int t2)
{
	return t1 > t2 ? t1 : t2;
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
%type type_name { decl_specif_t }
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
%type postfix_expression { expr_t* }
%type unary_expression { expr_t* }
%type cast_expression { expr_t* }
%type multiplicative_expression { expr_t* }
%type additive_expression { expr_t* }
%type shift_expression { expr_t* }
%type relational_expression { expr_t* }
%type equality_expression { expr_t* }
%type and_expression { expr_t* }
%type exclusive_or_expression { expr_t* }
%type inclusive_or_expression { expr_t* }
%type logical_and_expression { expr_t* }
%type logical_or_expression { expr_t* }
%type assignment_expression { expr_t* }
%type initializer { expr_t* }
%type unary_operator { int }

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
	if (sym == nullptr)
	{
		yyerror("symbol not found");
	}
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
primary_expression(R) ::= LP expression(A) RP. { R = A; }

postfix_expression(R) ::= primary_expression(A). { R = A; }
postfix_expression(R) ::= postfix_expression(A) LS expression(B) RS. {
	if (A->depth == 0)
	{
		yyerror("indexing on non-pointer type");
	}
	if (B->depth != 0)
	{
		yyerror("attempt to use pointer as RHS");
	}

	int elemsize = get_size(A->type, A->depth-1);

	expr_t* index = new expr_t;
	index->category = CATEGORY_COMBINED;
	index->left = true;

	index->type = A->type;
	index->depth = A->depth;
	index->op = OP_ADD;
	index->lhs = A;
	index->rhs = B;
	R = index;
}
//postfix_expression(R) ::= postfix_expression LP RP.
//postfix_expression(R) ::= postfix_expression LP argument_expression_list RP.
postfix_expression(R) ::= postfix_expression(A) INC_OP. {
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = A->type;
	ex->depth = A->depth;
	ex->op = OP_POST_INC;
	ex->lhs = A;
	R = ex;
}
postfix_expression(R) ::= postfix_expression(A) DEC_OP. {
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = A->type;
	ex->depth = A->depth;
	ex->op = OP_POST_DEC;
	ex->lhs = A;
	R = ex;
}

//argument_expression_list ::= assignment_expression.
//argument_expression_list ::= argument_expression_list COM assignment_expression.

unary_expression(R) ::= postfix_expression(A). { R = A; }
unary_expression(R) ::= INC_OP unary_expression(A). {
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = A->type;
	ex->depth = A->depth;
	ex->op = OP_PRE_INC;
	ex->lhs = A;
	R = ex;
}
unary_expression(R) ::= DEC_OP unary_expression(A). {
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = A->type;
	ex->depth = A->depth;
	ex->op = OP_PRE_DEC;
	ex->lhs = A;
	R = ex;
}
unary_expression(R) ::= unary_operator(A) cast_expression(B). {
	if (A == OP_ADD)
	{
		R = B;
	}
	else
	{
		expr_t* ex = new expr_t;
		ex->category = CATEGORY_COMBINED;
		ex->type = B->type;
		ex->op = OP_PRE_DEC;
		ex->lhs = B;
		if (A == OP_REF)
		{
			ex->depth = B->depth + 1;
			ex->left = false;
		}
		else if (A == OP_DEREF)
		{
			if (B->depth == 0)
			{
				yyerror("attempted to dereference a non-pointer value");
			}
			ex->depth = B->depth - 1;
			ex->left = true;
		}
		else
		{
			ex->depth = B->depth;
			ex->left = false;
		}
		R = ex;
	}
}
unary_expression(R) ::= SIZEOF unary_expression(A). {
	int elemsize = get_size(A->type, A->depth);
	//TODO recursively free(A)

	R = new expr_t;
	R->category = CATEGORY_LITERAL;
	R->left = false;

	R->type = TYPE_INT;
	R->depth = 0;
	R->ival = elemsize;
}
unary_expression(R) ::= SIZEOF LP type_name(A) RP. {
	R = new expr_t;
	R->category = CATEGORY_LITERAL;
	R->left = false;

	R->type = TYPE_INT;
	R->depth = 0;
	R->ival = get_size(A.type, A.depth);
}

unary_operator(R) ::= AND_OP. { R = OP_REF; }
unary_operator(R) ::= MUL_OP. { R = OP_DEREF; }
unary_operator(R) ::= ADD_OP. { R = OP_ADD; }
unary_operator(R) ::= SUB_OP. { R = OP_SUB; }
unary_operator(R) ::= NOT_OP. { R = OP_NOT; }
unary_operator(R) ::= LOGNOT. { R = OP_LOGNOT; }

cast_expression(R) ::= unary_expression(A). { R = A; }
cast_expression(R) ::= LP type_name(A) RP cast_expression(B). {
	if (convertible(B, A))
	{
		B->type = A.type;
		B->depth = A.depth;
		R = B;
	}
	else
	{
		yyerror("bad cast");
	}
}

multiplicative_expression(R) ::= cast_expression(A). { R = A; }
multiplicative_expression(R) ::= multiplicative_expression(A) MUL_OP cast_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_MUL;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
multiplicative_expression(R) ::= multiplicative_expression(A) DIV_OP cast_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_DIV;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
multiplicative_expression(R) ::= multiplicative_expression(A) MOD_OP cast_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_MOD;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

additive_expression(R) ::= multiplicative_expression(A). { R = A; }
additive_expression(R) ::= additive_expression(A) ADD_OP multiplicative_expression(B). {
	if (B->depth != 0)
	{
		yyerror("attempt to use pointer as RHS");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = A->left;
	ex->type = hybrid(A->type, B->type);
	ex->depth = A->depth == 0 ? hybrid(A->type, B->type) : A->type;
	ex->op = OP_ADD;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
additive_expression(R) ::= additive_expression(A) SUB_OP multiplicative_expression(B). {
	if (B->depth != 0)
	{
		yyerror("attempt to use pointer as RHS");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = A->left;
	ex->type = A->depth == 0 ? hybrid(A->type, B->type) : A->type;
	ex->depth = A->depth;
	ex->op = OP_SUB;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

shift_expression(R) ::= additive_expression(A). { R = A; }
shift_expression(R) ::= shift_expression(A) SHL_OP additive_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_SHL;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
shift_expression(R) ::= shift_expression(A) SHR_OP additive_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_SHR;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

relational_expression(R) ::= shift_expression(A). { R = A; }
relational_expression(R) ::= relational_expression(A) LT_OP shift_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_LT;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
relational_expression(R) ::= relational_expression(A) GT_OP shift_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_GT;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
relational_expression(R) ::= relational_expression(A) LE_OP shift_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_LE;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
relational_expression(R) ::= relational_expression(A) GE_OP shift_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_GE;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

equality_expression(R) ::= relational_expression(A). { R = A; }
equality_expression(R) ::= equality_expression(A) EQ_OP relational_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_EQ;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}
equality_expression(R) ::= equality_expression(A) NE_OP relational_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_NE;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

and_expression(R) ::= equality_expression(A). { R = A; }
and_expression(R) ::= and_expression(A) AND_OP equality_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_AND;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

exclusive_or_expression(R) ::= and_expression(A). { R = A; }
exclusive_or_expression(R) ::= exclusive_or_expression(A) OR_OP and_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_OR;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

inclusive_or_expression(R) ::= exclusive_or_expression(A). { R = A; }
inclusive_or_expression(R) ::= inclusive_or_expression(A) XOR_OP exclusive_or_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_XOR;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

logical_and_expression(R) ::= inclusive_or_expression(A). { R = A; }
logical_and_expression(R) ::= logical_and_expression(A) LOGAND inclusive_or_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_LOGAND;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

logical_or_expression(R) ::= logical_and_expression(A). { R = A; }
logical_or_expression(R) ::= logical_or_expression(A) LOGOR logical_and_expression(B). {
	if (A->depth != 0 || B->depth != 0)
	{
		yyerror("non-add/sub-arithmetic on pointer");
	}
	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = hybrid(A->type, B->type);
	ex->depth = 0;
	ex->op = OP_LOGOR;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

assignment_expression(R) ::= unary_expression(A) ASGN_OP logical_or_expression(B). {
	if (!A->left)
	{
		yyerror("attempt to assign to a right value");
	}

	if (A->depth != B->depth)
	{
		yyerror("pointer depth mismatch");
	}
	else
	{
		if (A->type != B->type)
		{
			yyerror("pointer type mismatch");
		}
	}

	expr_t* ex = new expr_t;
	ex->category = CATEGORY_COMBINED;
	ex->left = false;
	ex->type = A->depth == 0 ? hybrid(A->type, B->type) : A->type;
	ex->depth = A->depth;
	ex->op = OP_ASGN;
	ex->lhs = A;
	ex->rhs = B;
	R = ex;
}

expression(R) ::= assignment_expression(A). { R = A; }

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
init_declarator(R) ::= declarator(A) ASGN_OP initializer(B). {
	//A.init = B;
	//R = A;
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

type_name(R) ::= declaration_specifiers(A). { R = A; }
type_name(R) ::= declaration_specifiers(A) pointer(B). {
	A.depth = B; 
	R = A; 
}

//initializer(R) ::= logical_or_expression(A).

statement ::= labeled_statement.
statement ::= compound_statement.
statement ::= expression_statement.
statement ::= selection_statement.
statement ::= iteration_statement.
statement ::= jump_statement.

labeled_statement ::= ID COL statement.

block_begin ::= LB. { next_scope(); }
block_end ::= RB. { exit_scope(); }

compound_statement ::= block_begin block_end.
compound_statement ::= block_begin block_item_list block_end.

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
