#pragma once

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
