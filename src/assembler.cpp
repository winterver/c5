#include "assembler.hpp"
#include "instructions.hpp"
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>

void print_assembly(std::string& str)
{
	std::istringstream is(str);
	image img;
	int op;

	while(is >> op)
	{
		bool operand = false;
		switch(op)
		{
		case EXIT: std::cout << "EXIT\n"; break; 
		case PRTF: std::cout << "RPTF\n"; break;

		case LOB: std::cout << "LOB\n"; break;
		case LOW: std::cout << "LOW\n"; break;
		case LOD: std::cout << "LOD\n"; break;
		case LOQ: std::cout << "LOQ\n"; break;
		case STB: std::cout << "STB\n"; break;
		case STW: std::cout << "STW\n"; break;
		case STD: std::cout << "STD\n"; break;
		case STQ: std::cout << "STQ\n"; break;
		case PUB: std::cout << "PUB\n"; break;
		case PUW: std::cout << "PUW\n"; break;
		case PUD: std::cout << "PUD\n"; break;
		case PUQ: std::cout << "PUQ\n"; break;
		case POB: std::cout << "POB\n"; break;
		case POW: std::cout << "POW\n"; break;
		case POD: std::cout << "POD\n"; break;
		case POQ: std::cout << "POQ\n"; break;

		case RET: std::cout << "RET\n"; break;

		case ADD: std::cout << "ADD\n"; break;
		case SUB: std::cout << "SUB\n"; break;
		case MUL: std::cout << "MUL\n"; break;
		case DIV: std::cout << "DIV\n"; break;
		case MOD: std::cout << "MOD\n"; break;

		case AND: std::cout << "AND\n"; break;
		case OR:  std::cout << "OR\n"; break;
		case XOR: std::cout << "XOR\n"; break;

		case INC: std::cout << "INC\n"; break;
		case DEC: std::cout << "DEC\n"; break;
		case NEG: std::cout << "NEG\n"; break;

		case NOT: std::cout << "NOT\n"; break;

		case LAN: std::cout << "LAN\n"; break;
		case LOR: std::cout << "LOR\n"; break;
		case LNO: std::cout << "LNO\n"; break;

		case SHL: std::cout << "SHL\n"; break;
		case SHR: std::cout << "SHR\n"; break;

		case EQ: std::cout << "EQ\n"; break;
		case NE: std::cout << "NE\n"; break;
		case GT: std::cout << "GT\n"; break;
		case LT: std::cout << "LT\n"; break;
		case GE: std::cout << "GE\n"; break;
		case LE: std::cout << "NE\n"; break;

		default: operand = true; break;
		}

		if (operand)
		{
			if (op == JMP 
				//|| op == BNZ
				//|| op == BZ
				|| op == CAL
				|| op == LABL)
			{
				std::string label;
				is >> label;

				switch(op)
				{
				case JMP: std::cout << "JMP " << label << "\n"; break;
				//case BNZ: std::cout << "BNZ " << label << "\n"; break;
				//case BZ: std::cout << "BZ " << label << "\n"; break;
				case CAL: std::cout << "CAL " << label << "\n"; break;
				case LABL: std::cout << "Label " << label << "\n"; break;
				}
			}
			else
			{
				int num;
				is >> num;
				switch(op)
				{
				case IMB: std::cout << "IMB " << num << "\n"; break;
				case IMW: std::cout << "IMW " << num << "\n"; break;
				case IMD: std::cout << "IMD " << num << "\n"; break;
				case IMQ: std::cout << "IMQ " << num << "\n"; break;	
				case ADS: std::cout << "ADS " << num << "\n"; break;
				case LEA: std::cout << "LEA " << num << "\n"; break;
				case GLO: std::cout << "GLO " << num << "\n"; break;
				}
			}
		}
	}
}

image assemble(std::string& str)
{
	std::istringstream is(str);
	image img;
	int op;

	std::map<std::string, size_t> addresses;
	std::vector<std::pair<std::string, size_t>> references;

	while(is >> op)
	{
		bool operand = false;
		switch(op)
		{
		case EXIT: 
		case PRTF: 

		case LOB: 
		case LOW:
		case LOD: 
		case LOQ: 
		case STB: 
		case STW: 
		case STD: 
		case STQ: 
		case PUB: 
		case PUW: 
		case PUD: 
		case PUQ: 
		case POB: 
		case POW: 
		case POD: 
		case POQ: 

		case RET:

		case ADD: 
		case SUB: 
		case MUL: 
		case DIV: 
		case MOD: 

		case AND: 
		case OR: 
		case XOR: 

		case INC: 
		case DEC: 
		case NEG: 

		case NOT: 

		case LAN: 
		case LOR: 
		case LNO: 

		case SHL:
		case SHR:

		case EQ: 
		case NE:
		case GT: 
		case LT: 
		case GE: 
		case LE: 
			// opcodes without operand
			img.fill_text(op_t(op));
			break;
		default:
			operand = true;
			break;
		}
		
		if (operand)
		{
			if (op == JMP 
				//|| op == BNZ
				//|| op == BZ
				|| op == CAL
				|| op == LABL)
			{
				std::string label;
				is >> label;

				switch(op)
				{
				case JMP:	
				//case BNZ:
				//case BZ:
				case CAL:
					img.fill_text(op_t(op), u32());
					references.push_back(
						std::make_pair(label, img.text.size()-4));
					break;
				case LABL:
					addresses[label] = img.text.size();
					break;
				}
			}
			else
			{
				int num;
				is >> num;
				switch(op)
				{
				case IMB: img.fill_text(op_t(op), i8(num)); break;
				case IMW: img.fill_text(op_t(op), i16(num)); break;
				case IMD: img.fill_text(op_t(op), i32(num)); break;
				case IMQ: img.fill_text(op_t(op), i64(num)); break;	
				case ADS: img.fill_text(op_t(op), i16(num)); break;
				case LEA: img.fill_text(op_t(op), i16(num)); break;
				case GLO: img.fill_text(op_t(op), u32(num)); break;
				}
			}
		}	
	}

	bool fail = false;
	for(auto& x : references)
	{
		if (addresses.find(x.first) != addresses.end())
		{
			*(u32*)(img.text.data() + x.second)
				= addresses[x.first];
		}
		else
		{
			fail = true;
			std::cout << "undefined symbol: " << x.first << "\n";
		}
	}

	if (fail)
	{
		exit(-1);
	}

	return img;
}