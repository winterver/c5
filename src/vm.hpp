#pragma once
#include <assert.h>
#include "types.hpp"

enum op_t : u8 {
	EXIT,
	PRTF, // printf("%d", acc32);
	
	// IM: IMmediate, LO: LOad, ST: STore
	// PU: PUsh, PO: POp.
	// B: Byte, W: Word, D: Dword, Q: Qword

	IMB, 
	IMW, 
	IMD, 
	IMQ, 
	LOB, 
	LOW, 
	LOD, 
	LOQ, 
	STB, 
	STW, 
	STD, 
	STQ, 
	PUB, 
	PUW, 
	PUD, 
	PUQ, 
	POB, 
	POW, 
	POD, 
	POQ, 
	
	JMP, 
	BNZ, 
	BZ,	 
	CAL, // call 
	RET, 

	ADS, // add to stack
	LEA,	

	ADD, 
	SUB, 
	MUL,
	DIV,
	MOD,

	// bitwise operators
	AND,
	OR,
	XOR,

	INC,
	DEC,
	NEG,

	NOT, // bitwise not

	// logic operators
	LAN, // logic ANd
	LOR, // logic OR
	LNO, // logic NOt
	
	// comparison operators
	EQ,
	GT,
	LT,
	GE,
	LE,
};

class image;

class vm_t
{
public:
	vm_t(image& img, int stack_size_kb = 16);
	~vm_t();
	
	void exec();

	template<typename T>
	T& deref() {
		assert((acc != 0) && "virtual machine: null pointer dereference");
		return *(T*)acc;
	}

	template<typename T>
	void push(T t) { 
		sp -= sizeof(T);
		assert((sp >= stack) && "virtual machine: stack overflow");
		*(T*)sp = t; 
	}
	template<typename T>
	T pop() { T t = *(T*)sp; sp += sizeof(T); return t; }
	template<typename T>
	T next() { T t = *(T*)op; op += sizeof(T); return t; }	

public:
	u8* const text;
	u8* const stack;
	u8* const data;

	// registers
	u8* op;		// program counter
	i64 acc;	// accumulator	
	// float register
	//union {
	//	float flt32;
	//	double flt64;
	//};
	// stack pointers
	u8* sp; 
	u8* bp;	
};
