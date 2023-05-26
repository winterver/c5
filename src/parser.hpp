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

struct typeinfo
{
	int type;
	char* struct_name;
	int depth;

	typeinfo() { }
	typeinfo(int type, char* struct_name, int depth);
	bool operator==(typeinfo& rhs);
	bool operator!=(typeinfo& rhs);
};

struct param
{
	typeinfo tinfo;
	char* name;
};

struct function
{
	typeinfo tinfo;
	char* name;
	std::vector<param> params;
	int addr;
};

struct variable
{
	typeinfo tinfo;
	char* name;
	int addr;
};

class variable_set : public std::vector<variable>
{
public:
	variable* get(char* name)
	{
		auto r = std::find_if(begin(), end(),
			[name] (auto& x) { return name == x.name; });
		return r != end() ? &(*r) : nullptr;
	}
};

class function_set : public std::vector<function>
{
public:
	function* get(char* name)
	{
		auto r = std::find_if(begin(), end(),
			[name] (auto& x) { return name == x.name; });
		return r != end() ? &(*r) : nullptr;
	}
};

class buffer;
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
	function_set funcs;
	variable_set gvars;
};
