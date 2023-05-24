#pragma once

struct token
{
	int tok;
	union {
		unsigned long long int ival;
		long double fval;
		char* sval;
	};
};
