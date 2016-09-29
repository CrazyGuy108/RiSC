#include "utilities.h"

const Table<operation_t> ops
{
	{ ".fill",  &fill },
	{ ".space", &space },
	{ "add",    &add },
	{ "addi",   &addi },
	{ "beq",    &beq },
	{ "halt",   &halt },
	{ "jalr",   &jalr },
	{ "lli",    &lli },
	{ "lui",    &lui },
	{ "lw",	    &lw },
	{ "movi",   &movi },
	{ "nand",   &nand },
	{ "nop",    &nop },
	{ "sw",	    &sw }
};

const Table<inst_t> regs
{
	{ "0",	0x0000 },
	{ "1",	0x0001 },
	{ "2",	0x0002 },
	{ "3",	0x0003 },
	{ "4",	0x0004 },
	{ "5",	0x0005 },
	{ "6",	0x0006 },
	{ "7",	0x0007 },
	{ "r0", 0x0000 },
	{ "r1", 0x0001 },
	{ "r2", 0x0002 },
	{ "r3", 0x0003 },
	{ "r4", 0x0004 },
	{ "r5", 0x0005 },
	{ "r6", 0x0006 },
	{ "r7", 0x0007 }
};

Table<inst_t> symbols;

int cmp(const char* a, const char* b)
{
	size_t index{ 0 };

	do
	{
		if (a[index] < b[index])
			return -1;
		else if (a[index] > b[index])
			return 1;
		else
			++index;
	} while (a[index] && b[index]);

	return 0;
}

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

	int index{ regs.search(name) };

	if (index > 0)
		return regs[index];
	else
		; // error: unknown register name
}

inst_t imm(const char* name, uint16_t line /* = 0 */, inst_t mask /*= 0xffff*/)
{
	char* endp;
	long value{ strtol(name, &endp, 0) };

	if (endp != name) // is a number
	{
		if (value & mask == value)
			return (inst_t)value;
		else
			; // error: immediate too big
	}
	else // not a number but could be a symbol
	{
		int index{ symbols.search(name) };
		if (index >= 0)
			return symbols[index];
		else
			; // error: unresolved symbol
	}
	/*
	int index{ symbols.search(name) };

	// check if not in symbol table first
	if (index < 0)
		return (inst_t)strtoul(name, nullptr, 0); // add error checking later
	else
		return symbols[index] - line; // generates offset*/
}