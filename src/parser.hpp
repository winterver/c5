#pragma once

struct token
{
	int tok;
	union {
		long long int ival;
		long double fval;
		char* sval;
	};
};
