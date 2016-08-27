#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include "../symboltable/symboltable.h"

// opcode class
	// contains opcode number and inst. type(rrr, rri, ri probs enum/macro)
// in some other file make pseudo op class
	// gives data + conditional compilation(if needed) for how to translate

class Opcode
{
public:
	Opcode(const char* name);

	uint16_t value;
};

class Reg
{
public:
	Reg(const char* name);
	uint16_t value;
};

class RRR
{
public:
	RRR(const char* r1, const char* r2, const char* r3);
	const Reg data[3];
};

class Add
	: public Opcode, public RRR
{
public:
	Add(const char** operands);
};

#endif // OPCODES_H