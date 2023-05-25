#pragma once

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

class image;

class parser
{
public:
	parser(image& img, struct token* tok);

private:
	void error(const char* errmsg);

	int token();
	void match(int t);

private:
	struct token* tok;

private:
	image& img;
};
