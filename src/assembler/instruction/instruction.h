#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// prototypes
class Line;

#include <cstdint>
#include "../utilities/utilities.h"

#define A_SHIFT       13
#define B_SHIFT       10
#define IMM7_MASK     0x007f
#define IMM7_NEG_MASK 0xff80
#define IMM10_MASK    0x03ff

class Instruction
{
public:
	Instruction();
	Instruction(uint16_t value);

	uint16_t value;
};

class RRR
	: public Instruction
{
public:
	RRR(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t regC);
	RRR(uint16_t opcode, const char* regA, const char* regB, const char* regC);
};

class RRI
	: public Instruction
{
public:
	RRI(uint16_t opcode, uint16_t regA, uint16_t regB, uint16_t immC);
	RRI(uint16_t opcode, const char* regA, const char* regB, uint16_t immC);
};

class RI
	: public Instruction
{
public:
	RI(uint16_t opcode, uint16_t regA, uint16_t immB);
};

class Line
{
public:
	Line(Instruction* instructions, size_t length);
	~Line();

	/***** use vector and overload operator+? *****/

	// array of compiled instructions
	Instruction* instructions;

	// keeps track of how many Instructions
	size_t length;
};

// takes in a parsed line of code to produce a series of bytecode instructions
Line compile(size_t argc, const char** argv);

#endif // INSTRUCTION_H