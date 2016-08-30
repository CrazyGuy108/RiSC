#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// prototypes
enum class OpType;
class Opcode;
class Operand;
class Reg;
class Imm;
class OperandField;
class RRR;
class RRI;
class RI;
class Instruction;
class Line;

#include <cstdint>
#include "../table/table.h"
#include "../utilities/utilities.h"

// opcode enum and class

enum class OpType
{
	RRR,
	RRI,
	RI
};

class Opcode
{
public:
	Opcode();
	Opcode(uint16_t value, OpType type);

	uint16_t value;
	OpType type;
};

// operand class and inherited forms

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

// operand field class and inherited forms

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

// semi-compiled instruction class

class Instruction
{
public:
	~Instruction();

	Opcode opcode;
	OperandField* operands;
};

// instruction container class

class Line
{
public:
	Line(int argc, const char** argv);
	~Line();

	// array of Instructions to translate into
	Instruction* instructions;

	// keeps track of how many Instructions
	size_t length;
};

#endif // INSTRUCTION_H