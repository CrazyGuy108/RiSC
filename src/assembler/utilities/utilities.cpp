#include "utilities.h"

Table<uint16_t> opcodes
{
	{ "add",	ADD },
	{ "addi",	ADDI },
	{ "beq",	BEQ },
	{ "jalr",	JALR },
	{ "lui",	LUI },
	{ "lw",		LW },
	{ "nand",	NAND },
	{ "sw",		SW }
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