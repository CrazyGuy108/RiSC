#include "../include/machine.h"

void Machine::commit(Result& r)
{
	switch (r.dest)
	{
	case Result::REGISTERS:
		if (r.id < regs_count)
			regs[r.id] = r.value;
		else
			; // error: reg index out of range
		break;

	case Result::MEMORY:
		if (r.id < mem_length)
			mem[r.id] = r.value;
		else
			; // error: mem index out of range
		break;
	}
}
