#include <stdio.h>
#include "vm.hpp"

vm_t::vm_t(int text_size_kb, 
		int stack_size_kb)
	: text(new u8[text_size_kb * 1024])
	, stack(new u8[stack_size_kb * 1024])
{
	op = text;
	// stacks grow downward, so add its size
	sp = stack + stack_size_kb * 1024;
	bp = stack + stack_size_kb * 1024;
}

vm_t::~vm_t()
{
	delete text;
	delete stack;
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

		case IMB: acc = next<u8>(); break;
		case IMW: acc = next<u16>(); break;
		case IMD: acc = next<u32>(); break;
		case IMQ: acc = next<u64>(); break;
		case LOB: acc = *ptr8; break;
		case LOW: acc = *ptr16; break;
		case LOD: acc = *ptr32; break;
		case LOQ: acc = *ptr64; break;
		case STB: *ptr8 = pop<u64>(); break;
		case STW: *ptr16 = pop<u64>(); break;
		case STD: *ptr32 = pop<u64>(); break;
		case STQ: *ptr64 = pop<u64>(); break;
		case PUSH: push<u64>(acc); break;
		case POP: acc = pop<u64>(); break;

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
		case ADS: sp += next<i32>(); break;
		case LEA: acc = (u64)(bp + next<i32>()); break;	

		case ADD: acc += pop<u64>(); break;
		case SUB: acc -= pop<u64>(); break;
		
		case MUL: acc = (i64)acc * pop<i64>(); break;
		case DIV: acc = (i64)acc / pop<i64>(); break;
		case MOD: acc = (i64)acc % pop<i64>(); break;
		
		case AND: acc = (i64)acc & pop<i64>(); break;
		case OR: acc = (i64)acc | pop<i64>(); break;
		case XOR: acc = (i64)acc ^ pop<i64>(); break;

		case INC: acc++; break;
		case DEC: acc--; break;
		case NEG: acc = -(i64)acc; break;	
		
		case NOT: acc = ~acc; break;

		case LAN: acc = acc && pop<u64>(); break;
		case LOR: acc = acc || pop<u64>(); break;
		case LNO: acc = !acc; break;
		}
	}
Exit:
	return;
}

int main()
{
	vm_t vm;

	vm.fill(
		JMP, 18_u32,
		IMD, 123_i32,
		PUSH,
		IMD, -110_i32,
		MUL,
		RET,
		CAL, 5_u32,
		PRTF,
		EXIT
	);
	
	vm.op = vm.text;
	vm.exec();
}
