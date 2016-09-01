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
	: Operand{ imm(name) } {}

Imm::Imm(uint16_t value)
	: Operand{ value } {}

Imm6::Imm6(const char* name)
	: Imm{ imm(name) & 0x003f } {}

Imm10::Imm10(const char* name)
	: Imm{ imm(name) & 0x03ff } {}

RRR::RRR(const char* regA, const char* regB, const char* regC)
	: regA{ regA }, regB{ regB }, regC{ regC } {}

RRI::RRI(const char* regA, const char* regB, const char* immC)
	: regA{ regA }, regB{ regB }, immC{ immC } {}

RI::RI(const char* regA, const char* immB)
	: regA{ regA }, immB{ immB } {}

Instruction::Instruction()
	{}

Instruction::Instruction(Opcode opcode, OperandField* operands, size_t length)
	: opcode{ opcode }, operands{ operands }, length{ length } {}

Instruction::~Instruction()
{
	delete[] operands;
}

Line::Line(int argc, const char** argv)
{
	int index{ opcodes.search(argv[0]) };
	if (index >= 0)
	{
		const Opcode& op{ opcodes[index].value };

		instructions = new Instruction[1];
		instructions->opcode = op;
		length = 1;

		switch (op.type)
		{
		case OpType::RRR:
			if (argc == 4)
			{
				instructions->operands = new RRR{ argv[1], argv[2], argv[3] };
				instructions->length = 3;
			}
			else
				; // error: operand amount doesn't match

			break;

		case OpType::RRI:
			if (argc == 4)
			{
				instructions->operands = new RRI{ argv[1], argv[2], argv[3] };
				instructions->length = 3;
			}
			else
				; // error: operand amount doesn't match
			break;

		case OpType::RI:
			if (argc == 3)
			{
				instructions->operands = new RI{ argv[1], argv[2] };
				instructions->length = 2;
			}
			else
				; // error: operand amount doesn't match
			break;

		default:
			instructions->length = 0; // error: opcode type undefined (should never happen)
		}
	}
	else
	{
		index = pseudos.search(argv[0]);
		if (index >= 0)
			pseudos[index].value(this, argc, argv); // evaluate as pseudo op by calling the contained function
		else
			; // error: undefined opcode
	}
}

Line::~Line()
{
	delete instructions;
}