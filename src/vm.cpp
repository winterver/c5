#include <stdio.h>
#include "vm.hpp"

vm_t::vm_t(int text_size_kb, 
		int stack_size_kb,
		int data_size_kb) 	
	: text(new u8[text_size_kb * 1024])
	, stack(new u8[(stack_size_kb + data_size_kb) * 1024])
	, data(stack + stack_size_kb * 1024)
{
	op = (op_t*) text;
	// stacks grow downward, so add its size
	sp8 = stack + stack_size_kb * 1024;
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
		switch(*op++)
		{
		case EXIT: goto Exit;
		case PRTF: printf("%d\n", acc32); break;

		case IMD: acc32 = *ip32++; break;
		case LOD: acc32 = *ptr32; break;
		case STD: *ptr32 = *sp32++; break;
		case PUD: *--sp32 = acc32; break;
		case POD: acc32 = *sp32++; break;
		case JMP: op = (op_t*)(text + (*ip32++)); break;
		case BNZ: if(acc32) op += (i32)(*ip32++); else ip32++; break;
		case BZ:  if(!acc32) op += (i32)(*ip32++); else ip32++; break;
		case CAL: 
				  *--sp32 = (u8*)(++ip32) - text;	// push eip
				  op = (op_t*)(text + (*--ip32));	// jmp addr
				  *--sp32 = bp - stack;				// push ebp
				  bp = sp8;					  		// mov ebp, esp
				  break;
		case RET: 
				  sp8 = bp;							// mov esp, ebp
				  bp = stack + (*sp32++);			// pop ebp
				  op = (op_t*)(text + (*sp32++));	// pop eip
				  break;
		case ADS: sp8 += (i32)(*ip32++); break;
		case LEA: acc32 = bp - stack + (i32)(*ip32++) ; break;
		case ADD: acc32 += *sp32++; break;
		case SUD: acc32 -= *sp32++; break;
		}
	}
Exit:
	return;
}

int main()
{
	vm_t vm;

	vm.fill(
		JMP, 18_u32, // end
//calc:
		IMD, 123_u32,
		PUD,
		IMD, 110_u32,
		ADD,
		RET,
//end:
		CAL, 5_u32, // calc
		PRTF,
		EXIT
	);

	vm.op = (op_t*)vm.text;
	vm.exec();
}
