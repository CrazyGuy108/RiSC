#include "utilities.h"

Table<Opcode> opcodes
{
	{ "add",  { ADD,  OpType::RRR } },
	{ "addi", { ADDI, OpType::RRI } },
	{ "beq",  { BEQ,  OpType::RRI } },
	{ "jalr", { JALR, OpType::RRI } },
	{ "lui",  { LUI,  OpType::RI  } },
	{ "lw",	  { LW,   OpType::RRI } },
	{ "nand", { NAND, OpType::RRR } },
	{ "sw",	  { SW,   OpType::RRI } }
};

Table<uint16_t> regs
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

Table<uint16_t> imms;

Table<uint16_t> symbols;

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