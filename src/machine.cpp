#include "../include/machine.h"

uword_t& Machine::mem(uword_t addr)
{
	if (addr < ram_length)
		return ram[addr];
	else
		; // error: mem index out of range
}

uword_t& Machine::reg(uword_t addr)
{
	if (addr < regs_count)
	{
		if (!addr) // accessing zero register
			regs[0] = 0; // reading will always produce 0
		return regs[addr];
	}
	else
		; // error: reg index out of range
}
