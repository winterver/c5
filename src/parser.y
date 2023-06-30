
%{
#include <string.h>
#include <stdio.h>
int yylex(void);
void yyerror(const char* s);

#include "symtab.hpp"
#define ZERO(s) memset(&s, 0, sizeof(s))
#include <vector>

// states of the parser
bool declare;

// helper function
template<class T>
T* extract(std::vector<T>* vec)
{
	auto res = new T[vec->size()];
	std::copy(vec->begin(), vec->end(), res);
	delete vec; // remember to retrive size before calling extract()
	return res;
}
%}

%union {
	long long ival;
	long double fval;
	const char* sval;

	struct {
		int type; 
		int specif; 
		const char* name; // valid only if type == TYPE_TYPDEF
	} decl_specif;

	init_decl_t init_decl;
	std::vector<init_decl_t>* init_decl_list;

	param_t param;
	std::vector<param_t>* param_list;
}

%token<ival> NUM
%token<fval> DEC
%token<sval> ID STR

%token SIZEOF
%token PTR_OP INC_OP DEC_OP SHL_OP SHR_OP LE_OP GE_OP EQ_OP NE_OP
%token LOGAND LOGOR MULASGN DIVASGN MODASGN ADDASGN
%token SUBASGN SHLASGN SHRASGN ANDASGN ELLIPSIS
%token XORASGN ORASGN

%token TYPEDEF STATIC CONST
%token VOID CHAR SHORT INT LONG FLOAT DOUBLE
%token<sval> TYPE // for types defined with typedef
%token IF ELSE FOR WHILE DO CONTINUE BREAK RETURN GOTO

%type<decl_specif> declaration_specifiers
%type<decl_specif> storage_class_specifier
%type<decl_specif> type_specifier
%type<decl_specif> type_qualifier

%type<ival> pointer
%type<init_decl> direct_declarator
%type<init_decl> declarator
%type<init_decl> init_declarator
%type<init_decl_list> init_declarator_list

%type<param> parameter_declaration
%type<param_list> parameter_list

%start translation_unit

%%

primary_expression
	: ID
	| NUM
	| DEC
	| STR
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' ID
	| postfix_expression PTR_OP ID
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression SHL_OP additive_expression
	| shift_expression SHR_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression LOGAND inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression LOGOR logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MULASGN
	| DIVASGN
	| MODASGN
	| ADDASGN
	| SUBASGN
	| SHLASGN
	| SHRASGN
	| ANDASGN
	| XORASGN
	| ORASGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

declaration
	: declaration_specifiers init_declarator_list ';'
		{ 
			declare = false;

			for(auto idl = $2->begin(); idl != $2->end(); idl++)
			{
				if ($1.type == 0)
				{
					yyerror("no type specifier");
				}

				// if it is a typedef declaration
				if ($1.specif & SPECIF_TYPEDEF)
				{
					if (idl->category == CATEGORY_VAR 
						|| idl->category == CATEGORY_ARRAY)
					{
						sym_t* nt = insert(idl->name);
						nt->category = idl->category;
						nt->type = $1.type;
						nt->specif = $1.specif;
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

					// if $1.type is a type defined with typedef
					if ($1.type == TYPE_TYPEDEF)
					{
						sym_t* t = lookup_type($1.name);
						if (t == nullptr)
						{
							yyerror("no such type");
						}
						if ($1.specif & t->specif)
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
						var->type = $1.type;
						var->specif = $1.specif;
						var->depth = idl->depth;

						var->category = idl->category;
						var->nparams = idl->nparams;
						var->params = idl->params;
						var->variadic = idl->variadic;
					}
				}
			} // end foreach($2)
			delete $2;
		}
	;

declaration_specifiers
	: storage_class_specifier { $$ = $1; declare = true; }
	| declaration_specifiers storage_class_specifier 
		{
			if ($1.specif & $2.specif)
			{
				yyerror("duplicate specifier");
			}
			$1.specif |= $2.specif;
			$$ = $1;
			declare = true;
		}
	| type_specifier { $$ = $1; declare = true; }
	| declaration_specifiers type_specifier
		{
			if ($1.type != 0)
			{
				yyerror("multiple type specifier");
			}
			$1.type = $2.type;
			$1.name = $2.name;
			$$ = $1;
			declare = true;
		}
	| type_qualifier { $$ = $1; declare = true; }
	| declaration_specifiers type_qualifier
		{
			if ($1.specif & $2.specif)
			{
				yyerror("duplicate qualifier");
			}
			$1.specif |= $2.specif;
			$$ = $1;
			declare = true;
		}
	;

init_declarator_list
	: init_declarator
		{
			$$ = new std::vector<init_decl_t>;
			$$->push_back($1);
		}
	| init_declarator_list ',' init_declarator
		{
			// TODO: check duplicate names
			$1->push_back($3);
			$$ = $1;
		}
	;

init_declarator
	: declarator { $$ = $1; }
	| declarator '=' initializer
		{
			yyerror("initializer is currently not supported");
		}
	;

storage_class_specifier
	: TYPEDEF { ZERO($$); $$.specif = SPECIF_TYPEDEF; }
	| STATIC { ZERO($$); $$.specif = SPECIF_STATIC; }
	;

type_specifier
	: VOID { ZERO($$); $$.type = TYPE_VOID; }
	| CHAR { ZERO($$); $$.type = TYPE_CHAR; }
	| SHORT { ZERO($$); $$.type = TYPE_SHORT; }
	| INT { ZERO($$); $$.type = TYPE_INT; }
	| LONG { ZERO($$); $$.type = TYPE_LONG; }
	| TYPE { ZERO($$); $$.type = TYPE_TYPEDEF; $$.name = $1; }
	;

type_qualifier
	: CONST { ZERO($$); $$.specif = SPECIF_CONST; }
	;

specifier_qualifier_list
	: type_specifier
	| type_specifier specifier_qualifier_list
	| type_qualifier
	| type_qualifier specifier_qualifier_list;

declarator
	: pointer direct_declarator { $2.depth = $1; $$ = $2; }
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: ID { ZERO($$); $$.name = $1; $$.category = CATEGORY_VAR; }
	| direct_declarator '[' ']' { yyerror("array is currently not supported"); }
	| direct_declarator '[' assignment_expression ']' { yyerror("array is currently not supported"); }
	| direct_declarator '(' ')'
		{
			if ($1.category != CATEGORY_VAR)
			{
				yyerror("illegal function declaration");
			}
			$1.category = CATEGORY_FUNC;
			$$ = $1;
		}
	| direct_declarator '(' parameter_list ')'
		{
			if ($1.category != CATEGORY_VAR)
			{
				yyerror("illegal function declaration");
			}
			$1.category = CATEGORY_FUNC;
			$1.nparams = $3->size();
			$1.params = extract($3);
			$$ = $1;
		}
	| direct_declarator '(' parameter_list ',' ELLIPSIS ')'
		{
			if ($1.category != CATEGORY_VAR)
			{
				yyerror("illegal function declaration");
			}
			$1.category = CATEGORY_FUNC;
			$1.nparams = $3->size();
			$1.params = extract($3);
			$1.variadic = true;
			$$ = $1;
		}
	;

pointer
	: '*' { $$ = 1; }
	| '*' pointer { $$ = $2 + 1; }
	;

parameter_list
	: parameter_declaration
		{
			$$ = new std::vector<param_t>;
			$$->push_back($1);
		}
	| parameter_list ',' parameter_declaration
		{
			// TODO: check duplicate names
			$1->push_back($3);
			$$ = $1;
		}
	;

parameter_declaration
	: declaration_specifiers declarator
		{ 
			if ($2.category != CATEGORY_VAR)
			{
				yyerror("only value-type and pointers are supported in parameter list");
			}
			ZERO($$);
			$$.type = $1.type; 
			$$.specif = $1.specif;
			$$.depth = $2.depth;
			$$.name = $2.name;
			// TODO expand TYPE_TYPEDEF
		}
	| declaration_specifiers pointer
		{ 
			ZERO($$);
			$$.type = $1.type; 
			$$.specif = $1.specif;
			$$.depth = $2;
		}
	| declaration_specifiers
		{ 
			ZERO($$);
			$$.type = $1.type; 
			$$.specif = $1.specif;
		}
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list pointer
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: ID ':' statement
	;

compound_statement
	: '{' '}'
	| '{' block_item_list '}'
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	| FOR '(' declaration expression_statement ')' statement
	| FOR '(' declaration expression_statement expression ')' statement
	;

jump_statement
	: GOTO ID ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator compound_statement
	;

%%
