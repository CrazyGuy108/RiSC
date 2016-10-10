#include "../include/machine.h"

void Machine::write(Write& w)
{
	switch (w.unit)
	{
	case Memory::REGISTERS:
		if (w.addr < regs_count)
			regs[w.addr] = w.value;
		else
			; // error: reg index out of range
		break;

	case Memory::RAM:
		if (w.addr < ram_length)
			ram[w.addr] = w.value;
		else
			; // error: mem index out of range
		break;
	}
}
