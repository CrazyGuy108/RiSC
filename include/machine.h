#ifndef MACHINE_H
#define MACHINE_H

#include "read.h"      // for Read
#include "utilities.h" // for typedefs
#include "write.h"     // for Write

class Machine
{
public:
	uword_t read(Read& r);
	void write(Write& w);

private:
	uword_t ram[ram_length]  = {};
	uword_t regs[regs_count] = {};
};

#endif // MACHINE_H
