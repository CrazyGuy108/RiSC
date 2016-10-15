#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	RiSC machine;
	
	// load and execute bytecode
	machine.load(reinterpret_cast<data_t*>(contents), length);
	machine.execute();

	// print register contents
	for (size_t i{ 1 }; i < regs_count; ++i)
		std::cout << "r" << i << ": " << machine.getReg(i) << '\n';
}
