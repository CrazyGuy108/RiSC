#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	RiSC machine;
	
	// format bytes into 2byte instructions
	inst_t* code;
	for (size_t i{ 0 }; i < length; ++i)
		if (i % 2)
			code[i] = contents[i - 1] << 8 | contents[i];

	// load and execute bytecode
	machine.load(code, length / 2);
	machine.execute();

	// print register contents
	for (size_t i{ 1 }; i < regs_count; ++i)
		std::cout << "r" << i << ": " << machine.getReg(i) << '\n';
}
