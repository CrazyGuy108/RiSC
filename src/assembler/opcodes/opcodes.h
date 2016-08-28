#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include "../symboltable/symboltable.h"

typedef uint16_t Opcode;

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
	uint16_t value;
};

class Reg
	: public Operand
{
	
};

class Imm
	: public Operand
{
	
};

// operand field types

class OperandField
{

};

class RRR
	: public OperandField
{
public:
	RRR(const char* r1, const char* r2, const char* r3);

	Reg reg1, reg2, reg3;
};

class RRI
	: public OperandField
{
public:
	RRI(const char* r1, const char* r2, const char* i1);

	Reg reg1, reg2;
	Imm imm1;
};

class RI
	: public OperandField
{
public:
	RI(const char* r1, const char* i1);

	Reg reg1;
	Imm imm1;
};

#endif // OPCODES_H