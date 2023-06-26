#pragma once

struct sym_t
{
	sym_t* next;
	char* name;
	int type;
	int scope;
};

sym_t* insert(char* name);
sym_t* lookup(char* name);

void next_scope();
void exit_scope();
