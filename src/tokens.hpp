#pragma once

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
