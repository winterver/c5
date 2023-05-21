#pragma once
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define UDL(t) inline t operator ""_##t(unsigned long long int x) \
	{ return (t)x; }
UDL(i8); UDL(i16); UDL(i32); UDL(i64);
UDL(u8); UDL(u16); UDL(u32); UDL(u64);
#undef UDL

enum op_t : u8 {
	EXIT,
	PRTF, // printf("%d", acc32);
	
	// IM: IMmediate, LO: LOad, ST: STore
	// PU: PUsh, PO: POp.
	// B: Byte, W: Word, D: Dword, Q: Qword

		 // ARG		IMPL
	IMD, // u32		acc32 = *ip32++
	LOD, // 		acc32 = *ptr32
	STD, // 		*ptr32 = *sp32++
	PUD, //			*--sp32 = acc32
	POD, //			acc32 = *sp32++
	JMP, //	u32		op = text + (*ip32++)
	BNZ, // i32		if(acc32) op += (i32)(*ip32++); else ip32++;
	BZ,	 // i32		if(!acc32) op += (i32)(*ip32++) else ip32++;
	CAL, // u32		1: *--sp32 = (u8*)(++ip32) - text	// push eip
		 // 		2: op = text + (*--ip32)		// jmp addr
		 //			3: *--sp32 = bp - stack			// push ebp
		 //			4: bp = sp8						// mov ebp, esp
	RET, //			1: sp8 = bp						// mov esp, ebp
		 //			2: bp = stack + (*sp32++)		// pop ebp
		 //			3: op = text + (*sp32++)		// pop eip
	ADS, //	i32		sp8 += (i32)(*ip32++)
	LEA, // i32		acc32 = bp - stack + (i32)(*ip32++)
	
	ADD, //			acc32 += *sp32++
	SUD, //			acc32 -= *sp32++
};

class vm_t
{
public:
	vm_t(int text_size_kb = 32, 
		int stack_size_kb = 16,
		int data_size_kb = 16);
	~vm_t();
	
	void exec();

	template<typename T, typename... Ts>
	void fill(T t, Ts... ts) { fill(t); fill(ts...); }
	void fill(op_t o) { *op++ = o; }
	void fill(u32 o) { *ip32++ = o; }
	void fill() { }	

public:
	// segments
	u8* const text;
	u8* const stack; // stack and data point to the same
	u8* const data;	 // memory block. stack points to the
					 // initial, while data poiints to
					 // (stack + stack_size_kb*1024)

	// registers

	// program counter
	union {
		op_t* op;
		u8* ip8; 
		u16* ip16; 
		u32* ip32; 
		u64* ip64; 
	};
	// accumulator
	union {
		u8 acc8;
		u16 acc16;
		u32 acc32;
		u64 acc64;	
#define ptr8 ((u8*)(stack + acc32))
#define ptr16 ((u16*)(stack + acc32))
#define ptr32 ((u32*)(stack + acc32))
#define ptr64 ((u64*)(stack + acc32))
	};
	// float register
	union {
		float flt32;
		double flt64;
	};
	// stack pointer
	union { 
		u8* sp8; 
		u16* sp16; 
		u32* sp32; 
		u64* sp64; 
	};
	// base pointer
	u8* bp;	
};
