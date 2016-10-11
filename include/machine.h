#ifndef MACHINE_H
#define MACHINE_H

#include "read.h"      // for Read
#include "utilities.h" // for typedefs
#include "write.h"     // for Write

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
	uword_t read(MemUnit unit, uword_t addr);
	void write(MemUnit unit, uword_t addr, uword_t value);
	uword_t& access(MemUnit unit, uword_t addr);

	uword_t ram[ram_length]  = {};
	uword_t regs[regs_count] = {};
};

#endif // MACHINE_H
