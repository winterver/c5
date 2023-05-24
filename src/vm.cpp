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

		case IMB: acc = next<i8>(); break;
		case IMW: acc = next<i16>(); break;
		case IMD: acc = next<i32>(); break;
		case IMQ: acc = next<i64>(); break;
		case LOB: acc = deref<i8>(); break;
		case LOW: acc = deref<i16>(); break;
		case LOD: acc = deref<i32>(); break;
		case LOQ: acc = deref<i64>(); break;
		case STB: deref<i8>() = pop<i8>(); break;
		case STW: deref<i16>() = pop<i16>(); break;
		case STD: deref<i32>() = pop<i32>(); break;
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
		case BNZ: if(acc) op += next<i32>(); else next<i32>(); break;
		case BZ:  if(!acc) op += next<i32>(); else next<i32>(); break;
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

		case ADD: acc += pop<i64>(); break;
		case SUB: acc -= pop<i64>(); break;
		
		case MUL: acc *= pop<i64>(); break;
		case DIV: acc /= pop<i64>(); break;
		case MOD: acc %= pop<i64>(); break;
		
		case AND: acc &= pop<i64>(); break;
		case OR: acc |= pop<i64>(); break;
		case XOR: acc ^= pop<i64>(); break;

		case INC: acc++; break;
		case DEC: acc--; break;
		case NEG: acc = -acc; break;	
		
		case NOT: acc = ~acc; break;

		case LAN: acc = acc && pop<i64>(); break;
		case LOR: acc = acc || pop<i64>(); break;
		case LNO: acc = !acc; break;

		case EQ: acc = acc == pop<i64>();
		case GT: acc = acc > pop<i64>();
		case LT: acc = acc < pop<i64>();
		case GE: acc = acc >= pop<i64>();
		case LE: acc = acc <= pop<i64>();
		}
	}
Exit:
	return;
}
