
%{
#include <string.h>
#include "symtab.hpp"
int yylex(void);
void yyerror(const char* s);
#define ZERO(s) memset(&s, 0, sizeof(s))

// states of the parser
bool declare;
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
		}
	;

declaration_specifiers
	: storage_class_specifier { $$ = $1; declare = true; }
	| storage_class_specifier declaration_specifiers
		{
			if ($1.specif & $2.specif)
			{
				yyerror("duplicate specifier");
			}
			$2.specif |= $1.specif;
			$$ = $2;
			declare = true;
		}
	| type_specifier { $$ = $1; declare = true; }
	| type_specifier declaration_specifiers
		{
			if ($2.type != 0)
			{
				yyerror("duplicate specifier");
			}
			$2.type = $1.type;
			$2.name = $1.name;
			$$ = $2;
			declare = true;
		}
	| type_qualifier { $$ = $1; declare = true; }
	| type_qualifier declaration_specifiers
		{
			if ($1.specif & $2.specif)
			{
				yyerror("duplicate specifier");
			}
			$2.specif |= $1.specif;
			$$ = $2;
			declare = true;
		}
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
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
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: ID
	| direct_declarator '[' ']'
	| direct_declarator '[' assignment_expression ']'
	| direct_declarator '(' ')'
	| direct_declarator '(' parameter_list ')'
	| direct_declarator '(' parameter_list ',' ELLIPSIS ')'
	;

pointer
	: '*'
	| '*' pointer
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers
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
