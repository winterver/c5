%include {

#include <stdio.h>
#include <string.h>
#include <vector>
#include "symtab.hpp"

#define ZERO(s) memset(&s, 0, sizeof(s))
void yyerror(const char* s);

// states of the parser
bool declare;

struct decl_specif_t {
	int type; 
	int specif; 
	const char* name; // valid only if type == TYPE_TYPDEF
};

// helper function
template<class T>
T* extract(std::vector<T>* vec)
{
	auto res = new T[vec->size()];
	std::copy(vec->begin(), vec->end(), res);
	return res;
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
%type storage_class_specifier { decl_specif_t }
%type type_specifier { decl_specif_t }
%type type_qualifier { decl_specif_t }
%type pointer { int }
%type direct_declarator { init_decl_t }
%type declarator { init_decl_t }
%type init_declarator { init_decl_t }
%type init_declarator_list { std::vector<init_decl_t>* }
%type parameter_declaration { param_t }
%type parameter_list { std::vector<param_t>* }

%destructor init_declarator_list { delete $$; }
%destructor parameter_list { delete $$; }

%start_symbol start
start ::= .
start ::= translation_unit.

primary_expression ::= ID.
primary_expression ::= NUM.
primary_expression ::= DEC.
primary_expression ::= STR.
primary_expression ::= LP expression RP.

postfix_expression ::= primary_expression.
postfix_expression ::= postfix_expression LS expression RS.
postfix_expression ::= postfix_expression LP RP.
postfix_expression ::= postfix_expression LP argument_expression_list RP.
postfix_expression ::= postfix_expression DOT_OP ID.
postfix_expression ::= postfix_expression PTR_OP ID.
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

declaration ::= declaration_specifiers(A) init_declarator_list(B) SEM. {
	declare = false;

	for(auto idl = B->begin(); idl != B->end(); idl++)
	{
		if (A.type == 0)
		{
			yyerror("no type specifier");
		}

		// if it is a typedef declaration
		if (A.specif & SPECIF_TYPEDEF)
		{
			if (idl->category == CATEGORY_VAR 
				|| idl->category == CATEGORY_ARRAY)
			{
				sym_t* nt = insert(idl->name);
				nt->category = idl->category;
				nt->type = A.type;
				nt->specif = A.specif;
				nt->depth = idl->depth;
			}
			else
			{
				yyerror("unsupported typedef declaration");
			}
		}
		else { 
			// else it is a common declaration
			sym_t* var = insert(idl->name);

			// if A.type is a type defined with typedef
			if (A.type == TYPE_TYPEDEF)
			{
				sym_t* t = lookup_type(A.name);
				if (t == nullptr)
				{
					yyerror("no such type");
				}
				if (A.specif & t->specif)
				{
					yyerror("duplicate specifier");
				}

				var->type = t->type;
				// clear SPECIF_TYPEDEF flag and then combine
				var->specif |= t->specif & ~SPECIF_TYPEDEF;
				var->depth = t->depth + idl->depth;

				// if it's function or array, more steps are
				// required.
				if (idl->category == CATEGORY_FUNC)
				{
					if (t->category == CATEGORY_ARRAY)
					{
						yyerror("returning array is not supported");
					}
					var->category = CATEGORY_FUNC;
					var->nparams = idl->nparams;
					var->params = idl->params;
					var->variadic = idl->variadic;
				}
				else if (idl->category == CATEGORY_ARRAY
						|| t->category == CATEGORY_ARRAY)
				{
					var->category = CATEGORY_ARRAY;
					// TODO: combine their dimensions
				}			
			}
			// else it is a common type
			else
			{
				var->type = A.type;
				var->specif = A.specif;
				var->depth = idl->depth;

				var->category = idl->category;
				var->nparams = idl->nparams;
				var->params = idl->params;
				var->variadic = idl->variadic;
			}
		}
	} // end foreach(B)
}

declaration_specifiers(R) ::= storage_class_specifier(A). { R = A; declare = true; }
declaration_specifiers(R) ::= declaration_specifiers(A) storage_class_specifier(B). {
	if (A.specif & B.specif)
	{
		yyerror("duplicate specifier");
	}
	A.specif |= B.specif;
	R = A;
	declare = true;
}

declaration_specifiers(R) ::= type_specifier(A). { R = A; declare = true; }
declaration_specifiers(R) ::= declaration_specifiers(A) type_specifier(B). {
	if (A.type != 0)
	{
		yyerror("multiple type specifier");
	}
	A.type = B.type;
	A.name = B.name;
	R = A;
	declare = true;
}

declaration_specifiers(R) ::= type_qualifier(A). { R = A; declare = true; }
declaration_specifiers(R) ::= declaration_specifiers(A) type_qualifier(B). {
	if (A.specif & B.specif)
	{
		yyerror("duplicate qualifier");
	}
	A.specif |= B.specif;
	R = A;
	declare = true;
}

init_declarator_list(R) ::= init_declarator(A). {
	R = new std::vector<init_decl_t>;
	R->push_back(A);
}
init_declarator_list(R) ::= init_declarator_list(A) COM init_declarator(B). {
	// TODO: check duplicate names
	A->push_back(B);
	R = A;
}

init_declarator(R) ::= declarator(A). { R = A; }
init_declarator ::= declarator ASGN_OP initializer. {
	yyerror("initializer is currently not supported");
}

storage_class_specifier(R) ::= TYPEDEF. { ZERO(R); R.specif = SPECIF_TYPEDEF; }
storage_class_specifier(R) ::= STATIC. { ZERO(R); R.specif = SPECIF_STATIC; }

type_specifier(R) ::= VOID. { ZERO(R); R.type = TYPE_VOID; }
type_specifier(R) ::= CHAR. { ZERO(R); R.type = TYPE_CHAR; }
type_specifier(R) ::= SHORT. { ZERO(R); R.type = TYPE_SHORT; }
type_specifier(R) ::= INT. { ZERO(R); R.type = TYPE_INT; }
type_specifier(R) ::= LONG. { ZERO(R); R.type = TYPE_LONG; }
type_specifier(R) ::= TYPE(A). { ZERO(R); R.type = TYPE_TYPEDEF; R.name = A.sval; }

type_qualifier(R) ::= CONST. { ZERO(R); R.specif = SPECIF_CONST; }

specifier_qualifier_list ::= type_specifier.
specifier_qualifier_list ::= type_specifier specifier_qualifier_list.
specifier_qualifier_list ::= type_qualifier.
specifier_qualifier_list ::= type_qualifier specifier_qualifier_list.

declarator(R) ::= pointer(A) direct_declarator(B). { B.depth = A; R = B; }
declarator(R) ::= direct_declarator(A). { R = A; }

direct_declarator(R) ::= ID(A). { ZERO(R); R.name = A.sval; R.category = CATEGORY_VAR; }
direct_declarator ::= direct_declarator LS RS. { yyerror("array is currently not supported"); }
direct_declarator ::= direct_declarator LS assignment_expression RS. { yyerror("array is currently not supported"); }
direct_declarator(R) ::= direct_declarator(A) LP RP. {
	if (A.category != CATEGORY_VAR)
	{
		yyerror("illegal function declaration");
	}
	A.category = CATEGORY_FUNC;
	R = A;
}
direct_declarator(R) ::= direct_declarator(A) LP parameter_list(B) RP. {
	if (A.category != CATEGORY_VAR)
	{
		yyerror("illegal function declaration");
	}
	A.category = CATEGORY_FUNC;
	A.nparams = B->size();
	A.params = extract(B);
	R = A;
}
direct_declarator(R) ::= direct_declarator(A) LP parameter_list(B) COM ELLIPSIS RP. {
	if (A.category != CATEGORY_VAR)
	{
		yyerror("illegal function declaration");
	}
	A.category = CATEGORY_FUNC;
	A.nparams = B->size();
	A.params = extract(B);
	A.variadic = true;
	R = A;
}

pointer(R) ::= MUL_OP. { R = 1; }
pointer(R) ::= MUL_OP pointer(A). { R = A + 1; }

parameter_list(R) ::= parameter_declaration(A). {
	R = new std::vector<param_t>;
	R->push_back(A);
}
parameter_list(R) ::= parameter_list(A) COM parameter_declaration(B). {
	// TODO: check duplicate names
	A->push_back(B);
	R = A;
}

parameter_declaration(R) ::= declaration_specifiers(A) declarator(B). { 
	if (B.category != CATEGORY_VAR)
	{
		yyerror("only value-type and pointers are supported in parameter list");
	}
	ZERO(R);
	R.type = A.type; 
	R.specif = A.specif;
	R.depth = B.depth;
	R.name = B.name;
	// TODO expand TYPE_TYPEDEF
}
parameter_declaration(R) ::= declaration_specifiers(A) pointer(B). { 
	ZERO(R);
	R.type = A.type; 
	R.specif = A.specif;
	R.depth = B;
}
parameter_declaration(R) ::= declaration_specifiers(A). { 
	ZERO(R);
	R.type = A.type; 
	R.specif = A.specif;
}

type_name ::= specifier_qualifier_list.
type_name ::= specifier_qualifier_list pointer.

initializer ::= assignment_expression.
initializer ::= LB initializer_list RB.
initializer ::= LB initializer_list COM RB.

initializer_list ::= initializer.
initializer_list ::= initializer_list COM initializer.

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

block_item ::= declaration.
block_item ::= statement.

expression_statement ::= SEM.
expression_statement ::= expression SEM.

selection_statement ::= IF LP expression RP statement.
selection_statement ::= IF LP expression RP statement ELSE statement.

iteration_statement ::= WHILE LP expression RP statement.
iteration_statement ::= DO statement WHILE LP expression RP SEM.
iteration_statement ::= FOR LP expression_statement expression_statement RP statement.
iteration_statement ::= FOR LP expression_statement expression_statement expression RP statement.
iteration_statement ::= FOR LP declaration expression_statement RP statement.
iteration_statement ::= FOR LP declaration expression_statement expression RP statement.

jump_statement ::= GOTO ID SEM.
jump_statement ::= CONTINUE SEM.
jump_statement ::= BREAK SEM.
jump_statement ::= RETURN SEM.
jump_statement ::= RETURN expression SEM.

translation_unit ::= external_declaration.
translation_unit ::= translation_unit external_declaration.

external_declaration ::= declaration.
external_declaration ::= function_definition.

function_definition ::= declaration_specifiers declarator compound_statement.

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
