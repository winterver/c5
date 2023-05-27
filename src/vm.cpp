#include <stdio.h>
#include "vm.hpp"
#include "image.hpp"
#include "instructions.hpp"

vm_t::vm_t(image& img, int stack_size_kb)
	: text(img.get_text())
	, data(img.get_data())
	, stack(new u8[stack_size_kb * 1024])
{
	op = text;
	// stacks grow downward, so add its size
	sp = stack + stack_size_kb * 1024;
	bp = stack + stack_size_kb * 1024;
}

vm_t::~vm_t()
{
	delete[] stack;
}

void vm_t::exec()
{
	while(true)
	{
		op_t _op = *(op_t*)op;
		op += sizeof(op_t);
		switch(_op)
		{
		case EXIT: goto Exit;
		case PRTF: printf("%d\n", (i32)acc); break;

		// tips
		// 1 while doing arithmetic
		// lhs is on the top of stack
		// and rhs is in acc. both are
		// i64.
		// 2 while storing some value into
		// a specific address, an i64 value
		// shall be put on the top of stack
		// the pointer shall be in acc.
		// 3 BNZ & BZ takes ABSOLUTE address

		case IMB: acc = next<i8>(); break;
		case IMW: acc = next<i16>(); break;
		case IMD: acc = next<i32>(); break;
		case IMQ: acc = next<i64>(); break;
		case LOB: acc = deref<i8>(); break;
		case LOW: acc = deref<i16>(); break;
		case LOD: acc = deref<i32>(); break;
		case LOQ: acc = deref<i64>(); break;
		case STB: deref<i8>() = pop<i64>(); break;
		case STW: deref<i16>() = pop<i64>(); break;
		case STD: deref<i32>() = pop<i64>(); break;
		case STQ: deref<i64>() = pop<i64>(); break;
		case PUB: push<i8>(acc); break;
		case PUW: push<i16>(acc); break;
		case PUD: push<i32>(acc); break;
		case PUQ: push<i64>(acc); break;
		case POB: acc = pop<i8>(); break;
		case POW: acc = pop<i16>(); break;
		case POD: acc = pop<i32>(); break;
		case POQ: acc = pop<i64>(); break;

		case JMP: op = text + next<u32>(); break;
		case BNZ: if(acc) op = text + next<u32>(); else next<u32>(); break;
		case BZ:  if(!acc) op = text + next<u32>(); else next<u32>(); break;
		case CAL: 
				  push<u32>(op + 4 - text);			// push eip
				  op = text + next<u32>();			// jmp addr
				  push<u32>(bp - stack);			// push ebp
				  bp = sp;					  		// mov ebp, esp
				  break;
		case RET: 
				  sp = bp;							// mov esp, ebp
				  bp = stack + pop<u32>();			// pop ebp
				  op = text + pop<u32>();			// pop eip
				  break;
		case ADS: sp += next<i16>(); break;
		case LEA: acc = (u64)(bp + next<i16>()); break;	
		case GLO: acc = (u64)(data + next<u32>()); break;

		case ADD: acc = pop<i64>() + acc; break;
		case SUB: acc = pop<i64>() - acc; break;
		
		case MUL: acc = pop<i64>() * acc; break;
		case DIV: acc = pop<i64>() / acc; break;
		case MOD: acc = pop<i64>() % acc; break;
		
		case AND: acc = pop<i64>() & acc; break;
		case OR: acc = pop<i64>() | acc; break;
		case XOR: acc = pop<i64>() ^ acc; break;

		case INC: acc++; break;
		case DEC: acc--; break;
		case NEG: acc = -acc; break;	
		
		case NOT: acc = ~acc; break;

		case LAN: acc = pop<i64>() && acc; break;
		case LOR: acc = pop<i64>() || acc; break;
		case LNO: acc = !acc; break;

		case SHL: acc = pop<i64>() << acc; break;
		case SHR: acc = pop<i64>() >> acc; break;

		case EQ: acc = pop<i64>() == acc; break;
		case NE: acc = pop<i64>() != acc; break;
		case GT: acc = pop<i64>() > acc; break;
		case LT: acc = pop<i64>() < acc; break;
		case GE: acc = pop<i64>() >= acc; break;
		case LE: acc = pop<i64>() <= acc; break;
		}
	}
Exit:
	return;
}
