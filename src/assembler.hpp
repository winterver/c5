#pragma once

/*
class std::string;

class assembler
{
public:
	assembler(std::string& src);
	image assemble();

private:
	std::string src;
};
*/

#include <string>
class image;
void assemble(image& img, std::string& str);
