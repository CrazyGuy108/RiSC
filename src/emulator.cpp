#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	static OPCODE((*const ops[8])){ &add, &addi, &nand, &lui, &sw, &lw, &beq, &jalr };

	uint16_t inst;

	for (size_t i{ 0 }; i < length >> 1; ++i)
	{
		inst = ((uint16_t*)contents)[i];
		ops[inst & op_mask >> op_shift](inst);
	}
}
