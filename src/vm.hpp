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

	// ADd SUb MUltiply DIvide MOd ANd OR XOr
	ADB, 
	ADW, 
	ADD, 
	ADQ, 
	SUB, 
	SUW, 
	SUD, 
	SUQ, 

	MUB,
	MUW,
	MUD,
	MUQ,
	DIB,
	DIW,
	DID,
	DIQ,
	MOB,
	MOW,
	MOD,
	MOQ,

	// bitwise operators
	ANB,
	ANW,
	AND,
	ANQ,
	ORB,
	ORW,
	ORD,
	ORQ,
	XOB,
	XOW,
	XOD,
	XOQ,

	INC,
	DEC,
	NEG,

	NOT, // bitwise not

	// logic operators
	LAN, // logic ANd
	LOR, // logic OR
	LNO, // logic NOt
};

class vm_t
{
public:
	vm_t(int text_size_kb = 48, 
		int stack_size_kb = 16);
	~vm_t();
	
	void exec();

	template<typename T>
	void push(T t) { sp -= sizeof(T); *(T*)sp = t; }
	template<typename T>
	T pop() { T t = *(T*)sp; sp += sizeof(T); return t; }
	template<typename T>
	T next() { T t = *(T*)op; op += sizeof(T); return t; }
	
	template<typename T, typename... Ts>
	void fill(T t, Ts... ts) { fill(t); fill(ts...); }
	void fill(op_t o) { *(op_t*)op = o; op += sizeof(op_t); }
	void fill(u32 o) { *(u32*)op = o; op += 4; }
	void fill(i32 o) { *(i32*)op = o; op += 4; }
	void fill() { }	

public:
	u8* const text;
	u8* const stack;

	// registers
	u8* op;		// program counter
	u64 acc;	// accumulator	
#define ptr8 ((u8*)acc)
#define ptr16 ((u16*)acc)
#define ptr32 ((u32*)acc)
#define ptr64 ((u64*)acc)
	// float register
	union {
		float flt32;
		double flt64;
	};
	// stack pointers
	u8* sp; 
	u8* bp;	
};
