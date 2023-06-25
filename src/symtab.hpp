#pragma once

struct sym_t
{
	sym_t* next;
	char* name;
	int type;
	int scope;
};
