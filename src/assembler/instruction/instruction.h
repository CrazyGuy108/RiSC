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
	Reg(uint16_t value);
	Reg(const char* name);
};

class Imm
	: public Operand
{
public:
	Imm(uint16_t value);
	Imm(const char* name);
};

class Imm6
	: public Imm
{
public:
	Imm6(const char* name);
};

class Imm10
	: public Imm
{
public:
	Imm10(uint16_t value);
	Imm10(const char* name);
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
	Imm6 immC;
};

class RI
	: public OperandField
{
public:
	RI(const char* regA, const char* immB);
	RI(Reg regA, Imm10 immb);

	Reg regA;
	Imm10 immB;
};

// semi-compiled instruction class

class Instruction
{
public:
	Instruction();
	Instruction(Opcode opcode, OperandField* operands, size_t length);
	~Instruction();

	Opcode opcode;
	OperandField* operands;
	size_t length;
};

// instruction container class

class Line
{
public:
	Line(int argc, const char** argv);
	~Line();

	// uses all the constructed object heiarchy to compile into a series of bytecode
	uint16_t compile();

	// array of Instructions to translate into
	Instruction* instructions;

	// keeps track of how many Instructions
	size_t length;
};

#endif // INSTRUCTION_H