#ifndef RISC_HPP
#define RISC_HPP

#include <iostream>      // for cout
#include "utilities.hpp" // for typedefs

class RiSC
{
public:
	RiSC();

	void load(const char* program, data_t length); // load a program into memory
	void execute(); // execute the program where the PC left off

	data_t getRam(data_t addr);
	data_t getReg(data_t addr);

private:
	data_t& mem(data_t addr);
	data_t& reg(data_t addr);

	data_t ram[ram_length];
	data_t regs[regs_count];

	data_t pc;
};

#endif // RISC_HPP
