#ifndef MACHINE_H
#define MACHINE_H

#include "utilities.h" // for typedefs

class Machine
{
public:
	// specifies which memory unit should be accessed
	enum MemUnit
	{
		REGISTERS, RAM
	};

	void execute(inst_t inst);

private:
	uword_t& mem(uword_t addr);
	uword_t& reg(uword_t addr);

	uword_t ram[ram_length]  = {};
	uword_t regs[regs_count] = {};
};

#endif // MACHINE_H
