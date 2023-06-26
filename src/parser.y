

%{
int yylex(void);
void yyerror(const char* s);
%}

%union {
	char* sval;
	unsigned long long ival;
	long double fval;
}

    // TOKENS
%token<sval> ID STR
%token<ival> NUM
%token<fval> DEC
    // keywords
%token VOID CHAR SHORT INT LONG FLOAT DOUBLE TYPE
%token IF ELSE WHILE FOR CONTINUE BREAK RETURN
%token SIZEOF
    // operators
%token LOGAND LOGOR
%token ASGN PLUSASGN MINUSASGN MULASGN DIVASGN MODASGN
%token SHLASGN SHRASGN ANDASGN ORASGN XORASGN
%token EQ NE LE GE SHL SHR
%token LOGNOT NOT INCR DECR
%token ARW

%start program

%%

prim: ID
    | NUM
    | DEC
    | STR
    | '(' expr ')';

post: prim
    | post '[' expr ']'
    | post '(' ')'
    | post '(' args ')'
    | post '.' ID
    | post ARW ID
    | post INCR
    | post DECR;

args: arg ',' args
    | arg;
arg: expr;

unary: post
    | INCR unary
    | DECR unary
    | unary_op cast
    | SIZEOF unary
    | SIZEOF '(' type ')';

unary_op: '&'
    | '*'
    | '+'
    | '-'
    | '~'
    | '!';

cast: unary
    | '(' type ')' cast;

mul: cast
    | mul '*' cast
    | mul '/' cast
    | mul '%' cast;

add: mul
    | add '+' mul
    | add '-' mul;

shift: add
    | shift SHL add
    | shift SHR add;

relat: shift
    | relat '<' shift
    | relat '>' shift
    | relat LE shift
    | relat GE shift;

equ: relat
    | equ EQ relat
    | equ NE relat;

and: equ
    | and '&' equ;

xor: and
    | xor '^' and;

or: xor
    | or '|' xor;

logand: or
	| logand LOGAND or;

logor: logand
    | logor LOGOR logand;

expr: logor
    | logor '?' expr ':' expr;

assign: unary assign_op expr;
assign_op: '='
    | PLUSASGN
    | MINUSASGN
    | MULASGN
    | DIVASGN
    | MODASGN
    | SHLASGN
    | SHRASGN
    | ANDASGN
    | ORASGN
    | XORASGN;

var: type names ';';

type: VOID
    | CHAR
    | SHORT
    | INT
    | LONG
    | FLOAT
    | DOUBLE
    | TYPE;

names: init_name
    | names ',' init_name;

init_name: name
    | name ASGN init;

name: stars direct
    | direct;

stars: stars '*'
    | '*';

direct: ID
    | ID '[' ']'
    | ID '[' expr ']';

init: expr
    | '{' '}'
    | '{' list '}'
    | '{' list ',' '}';

list: list ',' expr
    | expr;

sig: type name '(' ')'
    | type name '(' params ')';
params: params ',' param
    | param;
param: type name;

fwrd: sig ';';
func: sig block;

stmt: assign ';'
    | expr ';'
    | var;

stmts: stmts stmt
    | stmt;

block: '{' '}'
    | '{' stmts '}';

program: tops
tops: tops top
    | ;

top: var
    | fwrd
    | func;
