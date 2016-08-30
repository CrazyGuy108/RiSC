#include "instruction.h"

Opcode::Opcode()
	{}

Opcode::Opcode(uint16_t value, OpType type)
	: value{ value }, type{ type } {}

Operand::Operand(uint16_t value)
	: value{ value } {}

Reg::Reg(const char* name)
	: Operand{ regs[name].value } {}

Imm::Imm(const char* name)
	: Operand{ imms[name].value } {}

RRR::RRR(const char* regA, const char* regB, const char* regC)
	: regA{ regA }, regB{ regB }, regC{ regC } {}

RRI::RRI(const char* regA, const char* regB, const char* immC)
	: regA{ regA }, regB{ regB }, immC{ immC } {}

RI::RI(const char* regA, const char* immB)
	: regA{ regA }, immB{ immB } {}

Instruction::Instruction()
	{}

Instruction::~Instruction()
{
	delete[] operands;
}

Line::Line(int argc, const char** argv)
{
	// distinguish between op and pseudo-op
	int indexOp{ opcodes.search(argv[0]) };
	if (indexOp >= 0)
	{
		const Opcode& op{ opcodes[indexOp].value };

		instructions = new Instruction[1];
		instructions->opcode = op;

		switch (op.type)
		{
		case OpType::RRR:
			instructions->operands = new RRR{ argv[1], argv[2], argv[3] };
			length = 3;
			break;

		case OpType::RRI:
			instructions->operands = new RRI{ argv[1], argv[2], argv[3] };
			length = 3;
			break;

		case OpType::RI:
			instructions->operands = new RI{ argv[1], argv[2] };
			length = 2;
			break;

		default:
			length = 0; // cant figure out op type (should never happen)
		}
	}
	else
		; // evaluate as pseudo-op (semi-recursively?)
}

Line::~Line()
{
	delete instructions;
}