#ifndef RISC_HPP
#define RISC_HPP

#include <array>         // for array
#include <iostream>      // for cout
#include "utilities.hpp" // for typedefs

template<size_t len>
using Memory = std::array<data_t, len>;

class RiSC
{
public:
	RiSC();

	void load(const char* program, data_t length); // load a program into memory
	void execute(); // execute the program where the PC left off

private:
	data_t& reg(data_t addr);
	data_t reg(data_t addr) const;

	Memory<ram_length> ram;
	Memory<regs_count> regs;

	data_t pc;
};

#endif // RISC_HPP
