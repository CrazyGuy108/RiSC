#include "../include/operations.hpp"

Opcode::Opcode(OP((*func)), inst_t len)
	: func{ func }, len{ len } {}

OP((*Opcode::getFunc() const))
{
	return func;
}

inst_t Opcode::length() const
{
	return len;
}

OP(add)
{
	if (argc == 4)
		return line_t{ rrr(ADD, reg(argv[1]), reg(argv[2]), reg(argv[3])) };
	else
		throw OperandException{ "add", 3, argc - 1 };
}
/***** add try/catch error handling once implemented *****/
OP(addi)
{
	if (argc == 4)
		return line_t{ rri(ADDI, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "addi", 3, argc - 1 };
}

OP(nand)
{
	if (argc == 4)
		return line_t{ rrr(NAND, reg(argv[1]), reg(argv[2]), reg(argv[3])) };
	else
		throw OperandException{ "nand", 3, argc - 1 };
}

OP(lui)
{
	if (argc == 3)
		return line_t{ ri(LUI, reg(argv[1]), imm(argv[2]) >> lui_shift) };
	else
		throw OperandException{ "lui", 2, argc - 1 };
}

OP(sw)
{
	if (argc == 4)
		return line_t{ rri(SW, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "sw", 3, argc - 1 };
}

OP(lw)
{
	if (argc == 4)
		return line_t{ rri(LW, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "lw", 3, argc - 1 };
}

OP(beq)
{
	if (argc == 4)
		return line_t{ rri(BEQ, reg(argv[1]), reg(argv[2]), imm(argv[3]) - 1 - line) };
	else
		throw OperandException{ "beq", 3, argc - 1 };
}

OP(jalr)
{
	if (argc == 4)
		return line_t{ rri(JALR, reg(argv[1]), reg(argv[2]), imm(argv[3])) };
	else
		throw OperandException{ "jalr", 3, argc - 1 };
}

OP(nop) // translates to "add r0 r0 r0"
{
	if (argc == 1)
	{
		const char* translation[4]{ "add", "r0", "r0", "r0" };

		return add(4, translation, line);
	}
	else
		throw OperandException{ "nop", 0, argc - 1 };
}

OP(halt) // translates to "jalr r0 r0 <halt syscall id>"
{
	if (argc == 1)
	{
		const char* translation[4]{ "jalr", "r0", "r0", "1" }; // syscall id for halt will probably be 1

		return jalr(4, translation, line);
	}
	else
		throw OperandException{ "halt", 0, argc - 1 };
}

OP(lli) // translates to "addi rA rA imm"
{
	if (argc == 3)
	{
		const char* translation[4]{ "addi", argv[1], argv[1], argv[2] };

		return addi(4, translation, line);
	}
	else
		throw OperandException{ "lli", 2, argc - 1 };
}

OP(movi) // translates to "lui rA imm" + "lli rA imm"
{
	if (argc == 3)
	{
		const char* translation[4]{ "lui", argv[1], argv[2] };
		line_t ret;
		ret.reserve(2);

		line_t tmp{ lui(3, translation, line) }; // lui rA imm
		ret.insert(ret.end(), tmp.begin(), tmp.end());

		translation[0] = "lli";
		tmp = lli(3, translation, line); // lli rA, imm
		tmp[0] &= movi_mask; // imm{5:0}
		ret.insert(ret.end(), tmp.begin(), tmp.end());

		return ret;
	}
	else
		throw OperandException{ "movi", 2, argc - 1 };
}

OP(unknown)
{
	return line_t{};
}
