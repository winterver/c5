%option noyywrap
%option yylineno
%option nounistd

%{
#include "symtab.hpp"
#include <vector>
#include "y.tab.h"

#ifdef _WIN32
#  include <io.h>
#  define isatty _isatty 
#endif

#include <string>
void yyerror(const char* s);
static int identifier_or_type();
static void process_escape_sequence();
static const char* pool(const char* name);
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P			([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS			((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%%

	/* primitives */
"void"								{ return VOID; }
"char"								{ return CHAR; }
"short"								{ return SHORT; }
"int"								{ return INT; }
"long"								{ return LONG; }
"float"								{ return FLOAT; }
"double"							{ return DOUBLE; }

	/* specifiers */
"typedef"							{ return TYPEDEF; }
"static"							{ return STATIC; }
"const"								{ return CONST; }

	/* keywords */
"if"								{ return IF; }
"else"								{ return ELSE; }
"for"								{ return FOR; }
"while"								{ return WHILE; }
"do"								{ return DO; }
"continue"							{ return CONTINUE; }
"break"								{ return BREAK; }
"return"							{ return RETURN; }
"goto"								{ return GOTO; }

	/* identifier & string literal */
{L}({L}|{D})*						{
										yylval.sval = pool(yytext);
										return identifier_or_type();
									}
\"([^\\\"]|\\.)*\"  				{
										process_escape_sequence();
										// +1 to skip the initial "
										yylval.sval = pool(yytext+1);
										return STR;
									}
	/* hexdecimal & octal & decimal & char */
0[xX]{H}+{IS}?						{
										yylval.ival = std::stoll(yytext, nullptr, 16);
										return NUM;
									}
0[0-7]*[IS]?						{
										yylval.ival = std::stoll(yytext, nullptr, 8);
										return NUM;
									}
[1-9]{D}*{IS}?						{
										yylval.ival = std::stoll(yytext);
										return NUM;
									}
'(\\.|[^\\'\n])+'					{
										process_escape_sequence();
										// +1 to skip the initial '
										yylval.ival = *(yytext+1);
										return NUM;
									}
	/* floating point */
{D}+{E}{FS}?						{
										yylval.fval = std::stold(yytext);
										return DEC;
									}
{D}*"."{D}+{E}?{FS}?				{
										yylval.fval = std::stold(yytext);
										return DEC;
									}
{D}+"."{D}*{E}?{FS}?				{
										yylval.fval = std::stold(yytext);
										return DEC;
									}
0[xX]{H}+{P}{FS}?					{
										yylval.fval = std::stold(yytext);
										return DEC;
									}
0[xX]{H}*"."{H}+{P}?{FS}?     		{
										yylval.fval = std::stold(yytext);
										return DEC;
									}
0[xX]{H}+"."{H}*{P}?{FS}?     		{
										yylval.fval = std::stold(yytext);
										return DEC;
									}

	/* single-character operators & symbols */
[~!%^&*()\-+={}\[\]|;:<>,./]		{ return *yytext; }

	/* multi-character operators */
"=="								{ return EQ_OP; }
"!="								{ return NE_OP; }
">="								{ return GE_OP; }
"<="								{ return LE_OP; }
"+="								{ return ADDASGN; }
"-="								{ return SUBASGN; }
"*="								{ return MULASGN; }
"/="								{ return DIVASGN; }
"%="								{ return MODASGN; }
"&="								{ return ANDASGN; }
"|="								{ return ORASGN; }
"^="								{ return XORASGN; }
"&&"								{ return LOGAND; }
"||"								{ return LOGOR; }
"<<"								{ return SHL_OP; }
">>"								{ return SHR_OP; }
"<<="								{ return SHLASGN; }
">>="								{ return SHRASGN; }
"++"								{ return INC_OP; }
"--"								{ return DEC_OP; }
"->"								{ return PTR_OP; }
"..."								{ return ELLIPSIS; }

	/* comments & skips & error handle */
"//".*								{ /* DO NOTHING */ }
[ \r\n\t\v\f]						{ /* DO NOTHING */ }
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]	{ /* DO NOTHING */ }
[/][*]								{ yyerror("unclosed comment"); }
.									{ yyerror("unknown character"); }

%%

#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_set>
#include "symtab.hpp"
extern bool declare;

void yyerror(const char* s)
{ 
	printf("(%d) %s", yylineno, s); 
	exit(-1); 
}

static int identifier_or_type()
{
	if (declare)
	{
		return ID;	
	}
	return lookup_type(yylval.sval) ? TYPE : ID;
}

static void process_escape_sequence()
{
	char* p1 = yytext;
	char* p2 = yytext;
	char c = 0;

	while(*p2 != '\0')
	{
		if (*p2 == '\\')
		{
			p2++;
			switch(*p2)
			{
			// https://en.wikipedia.org/wiki/Escape_sequences_in_C
			case 'a': c = '\a'; break;
			case 'b': c = '\b'; break;
			case 'f': c = '\f'; break;
			case 'n': c = '\n'; break;
			case 'r': c = '\r'; break;
			case 't': c = '\t'; break;
			case 'v': c = '\v'; break;
			case '\\': c = '\\'; break;
			case '\'': c = '\''; break;
			case '\"': c = '\"'; break;
			case '\?': c = '\?'; break;
			default: yyerror("unknown escape sequence");
			}
		}
		else
		{
			c = *p2;
		}
		*p1++ = c;
		p2++;
	}
	// change the trailing " or ' to \0
	*(p1 - 1) = '\0';
}

// string pool
static const char* pool(const char* text)
{
	struct string_compare { 
		bool operator()(
			const char* s1, 
			const char* s2
		) const {
			return !strcmp(s1, s2);
		}
	};

	static std::unordered_set<
		const char*,
		std::hash<std::string>,
		string_compare
	> strings;
	
	auto it = strings.find(text);
	if (it != strings.end())
	{
		return *it;
	}

	char* dup = strdup(text);
	strings.insert(dup);
	return dup;
}
