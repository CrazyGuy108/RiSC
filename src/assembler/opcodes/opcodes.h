#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include "../symboltable/symboltable.h"
#include "../utilities/utilities.h"

typedef uint16_t Opcode;
class Instruction;
class OperandField;

class Line
{
public:
	Line(int argc, const char** argv);

	// array of Instructions to translate into
	Instruction* instructions;

	// keeps track of how many Instructions
	size_t length;
};

class Instruction
{
public:
	Instruction(int argc, const char** argv);
	~Instruction();

	Opcode opcode;
	OperandField* operands;
};

class Operand
{
public:
	Operand(uint16_t value);

	uint16_t value;
};

class Reg
	: public Operand
{
public:
	Reg(const char* name);
};

class Imm
	: public Operand
{
public:
	Imm(const char* name);
};

// operand field types

class OperandField
{

};

class RRR
	: public OperandField
{
public:
	RRR(const char* regA, const char* regB, const char* regC);

	Reg regA;
	Reg regB;
	Reg regC;
};

class RRI
	: public OperandField
{
public:
	RRI(const char* regA, const char* regB, const char* immC);

	Reg regA;
	Reg regB;
	Imm immC;
};

class RI
	: public OperandField
{
public:
	RI(const char* regA, const char* immB);

	Reg regA;
	Imm immB;
};

#endif // OPCODES_H