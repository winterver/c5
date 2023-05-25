#pragma once
#include <vector>

struct token
{
	int tok;
	int lineno;
	union {
		long long int ival;
		long double fval;
		char* sval;
	};
};

struct param
{
	int type;
	char* struct_name;
	int depth;
	char* name;
};

struct function
{
	int type;
	char* struct_name;
	int depth;
	char* name;
	std::vector<param> params;
	int addr;
};

class image;

class parser
{
public:
	parser(image& img, struct token* tok);

	void parse();

private:
	void error(const char* errmsg);

	struct token* tok;
	function* curfunc;

	int token();
	void match(int t);

	void program();
	void paramlist(std::vector<param>& params);
	void block();

public:
	image& img;
	std::vector<function> funcs;
};
