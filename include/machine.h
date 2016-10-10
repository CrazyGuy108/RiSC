#ifndef MACHINE_H
#define MACHINE_H

#include "result.h"    // for Result
#include "utilities.h" // for typedefs

class Machine
{
public:
	// commits a Result to memory
	void commit(Result& r);

private:
	data_t mem[mem_length]  = {};
	data_t regs[regs_count] = {};
};

#endif // MACHINE_H
