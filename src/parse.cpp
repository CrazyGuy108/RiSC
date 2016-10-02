#include "../include/parse.h"

inst_t reg(const char* name)
{
	static const Table<inst_t> regs
	{
		{ "r0",	0x0000 },
		{ "r1",	0x0001 },
		{ "r2",	0x0002 },
		{ "r3",	0x0003 },
		{ "r4",	0x0004 },
		{ "r5",	0x0005 },
		{ "r6",	0x0006 },
		{ "r7",	0x0007 }
	};

	return regs[name];
}

inst_t imm(const char* name)
{
	char* endp;
	long value{ strtol(name, &endp, 0) };

	return endp == name ? symbols[name] : (inst_t)value;
}

line_t compile(size_t argc, char** argv, uint16_t line)
{
	static const Table<Opcode> ops
	{
		{ "add",  { &add,  1 } },
		{ "addi", { &addi, 1 } },
		{ "beq",  { &beq,  1 } },
		{ "halt", { &halt, 1 } },
		{ "jalr", { &jalr, 1 } },
		{ "lli",  { &lli,  1 } },
		{ "lui",  { &lui,  1 } },
		{ "lw",   { &lw,   1 } },
		{ "movi", { &movi, 2 } },
		{ "nand", { &nand, 1 } },
		{ "nop",  { &nop,  1 } },
		{ "sw",   { &sw,   1 } }
	};

	if (argc > 0)
		return ops[argv[0]].getFunc()(argc, (const char**)argv, line);
	else
		; // error: undetected blank line (could be a label on a blank line)
}