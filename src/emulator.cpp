#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	RiSC machine;
	
	// format bytes into 2byte instructions
	inst_t* code{ new inst_t[length / 2] };
	for (size_t i{ 0 }; i < length; ++i)
		if (i % 2)
			code[i] = contents[i - 1] << 8 | contents[i];

	// load the bytecode
	machine.load(code, length / 2);
	delete[] code;

	// then execute it
	machine.execute();
}
