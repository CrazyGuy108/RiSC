#ifndef MACHINE_H
#define MACHINE_H

#include "utilities.h" // for typedefs
#include "write.h"     // for Write

class Machine
{
public:
	void write(Write& w);

private:
	data_t ram[ram_length]  = {};
	data_t regs[regs_count] = {};
};

#endif // MACHINE_H
