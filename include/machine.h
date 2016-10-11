#ifndef MACHINE_H
#define MACHINE_H

#include "read.h"      // for Read
#include "utilities.h" // for typedefs
#include "write.h"     // for Write

class Machine
{
public:
	void execute(inst_t inst);

private:
	uword_t read(Read r);
	void write(Write w);
	uword_t& access(Memory& m);

	uword_t ram[ram_length]  = {};
	uword_t regs[regs_count] = {};
};

#endif // MACHINE_H
