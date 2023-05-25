#include <stdio.h>
#include <stdlib.h>

#include "types.hpp"
#include "image.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "instructions.hpp"

parser::parser(image& img, struct token* tok)
	: img(img)
	, tok(tok)
{ }

void parser::parse()
{
	program();
}

void parser::error(const char* errmsg)
{
	printf("(%d) %s\n", tok->lineno, errmsg);
	exit(-1);
}

int parser::token()
{
	return tok->tok;
}

void parser::match(int t)
{
	if (t == token())
	{
		tok++;
	}
	else
	{
		error("token mismatch");
	}
}

void parser::program()
{
	while(token())
	{
		// type of variable or return type of the function
		int type;
		char* struct_name;
		int depth;

		// match a type or struct definition
		switch(token())
		{
		case CHAR:
		case SHORT:
		case INT:
		case LONG:
			type = token();
			match(type);
			break;
		case STRUCT:
			{
				type = STRUCT;
				match(STRUCT);
				struct_name = tok->sval;
				match(IDENTIFIER);
				// process struct definition
				if (token() == '{')
				{
					match('{');
					// TODO process struct body
					match('}');
					match(';');
					// next round
					continue;
				}
				// TODO register struct
			}	
			break;
		default:
			error("top-level can only contain "
				"vardef, funcdecl, funcdef or structdef");
		}

		// get the depth of the pointer
		// 0 indicates that it's not a pointer
		for(depth = 0; token() == '*'; depth++)
		{
			match('*');
		}

		// name of the variable or function
		char* name = tok->sval;
		match(IDENTIFIER);

		// if it's a function
		if (token() == '(')
		{
			// match parameter list
			std::vector<param> params;
			paramlist(params);

			function func;
			func.type = type;
			func.struct_name = type == STRUCT ? struct_name : nullptr;
			func.depth = depth;
			func.name = name;
			func.params = params;
			func.addr = -1; // -1 indicates forward declaration

			// check if the declaration already exists,
			auto decl = std::find_if(
				funcs.begin(), funcs.end(), 
				[&func](auto& rhs) {
					return func.name == rhs.name;	
				}
			);

			// function to compare parameter list
			auto compare = [](
				std::vector<param>& p1,
				std::vector<param>& p2
			)
			{
				if (p1.size() != p2.size())
				{
					return false;
				}

				int size = p1.size();
				for(int i = 0; i < size; i++)
				{
					if (p1[i].type != p2[i].type
						|| p1[i].struct_name != p2[i].struct_name
						|| p1[i].depth != p2[i].depth)
					{
						return false;
					}
				}
				return true;
			};

			// if yes, check if both declaration are the same
			if (decl != funcs.end())
			{	
				if (decl->type != func.type
					|| decl->struct_name != func.struct_name
					|| decl->depth != func.depth
					|| !compare(decl->params, func.params))
				{
					error("declaration mismatch");
				}
			}

			// if it's a function definition
			if (token() == '{')
			{
				if (decl != funcs.end())
				{
					// check if the found declaration
					// has function body
					if (decl->addr != -1)
					{
						error("function redefinition");
					}
				}

				// get start address of the function body
				func.addr = img.text.size();
				// parse function body
				curfunc = &func;
				block();

				if (decl == funcs.end())
				{
					funcs.push_back(func);
				}
				else
				{
					decl->addr = func.addr;
					// update parameter names
					decl->params = std::move(func.params);
				}
			}
			else
			{
				// else it's a forward declaration
				match(';');

				if (decl == funcs.end())
				{
					funcs.push_back(func);
				}
			}
		}
		else
		{
			// else it's a global variable
			
			// TODO register global variable info
			
			while(token() == ',')
			{
				match(',');

				for(depth = 0; token() == '*'; depth++)
				{
					match('*');
				}

				name = tok->sval;
				match(IDENTIFIER);

				// TODO register global variable info
			}
			match(';');
		}
	}
}

void parser::paramlist(std::vector<param>& params)
{
	match('(');

	if (token() == ')')
	{
		match(')');
		return;
	}

	// type of the current param
	int type;
	char* struct_name;
	// name of the parameter
	char* name;
	int depth;

NextParam:
	// match a type
	switch(token())
	{
	case CHAR:
	case SHORT:
	case INT:
	case LONG:
		type = token();
		match(type);
		break;
	case STRUCT:
		type = STRUCT;
		match(STRUCT);
		struct_name = tok->sval;
		match(IDENTIFIER);	
		break;
	default:
		error("a type name needed");
	}

	// get the depth of the pointer
	// 0 indicates that it's not a pointer
	for(depth = 0; token() == '*'; depth++)
	{
		match('*');
	}

	name = tok->sval;
	match(IDENTIFIER);

	param p;
	p.type = type;
	p.struct_name = type == STRUCT ? struct_name : nullptr;
	p.name = name;
	p.depth = depth;

	params.push_back(p);

	if (token() == ',')
	{
		match(',');
		goto NextParam;
	}

	match(')');
}

void parser::block()
{
	match('{');
	match('}');
}
