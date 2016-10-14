#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	RiSC machine;
	
	// execute code
	machine.execute(0, length);

	// print register contents
	for (size_t i{ 1 }; i < regs_count; ++i)
		std::cout << "r" << i << ": " << machine.getReg(i) << '\n';
}
