#ifndef MACHINE_H
#define MACHINE_H

#include "write.h"     // for Write
#include "utilities.h" // for typedefs

class Machine
{
public:
	// commits a Result to memory
	void commit(Write& r);

private:
	data_t ram[ram_length]  = {};
	data_t regs[regs_count] = {};
};

#endif // MACHINE_H
