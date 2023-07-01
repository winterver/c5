#pragma once

#define TYPE_VOID 1
#define TYPE_CHAR 2
#define TYPE_SHORT 3
#define TYPE_INT 4
#define TYPE_LONG 5
#define TYPE_FLOAT 6
#define TYPE_DOUBLE 7

struct token_value_t
{
	int type;
	union {
		long long ival;
		long double fval;
		const char* sval;
	};
};
