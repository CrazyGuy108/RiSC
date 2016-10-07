#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	std::cout << "Initializing memory...\n";

	uint16_t* mem{ new uint16_t[65536] };
	for (size_t i{ 0 }; i < 65536; ++i)
		mem[i] = 0;

	uint16_t inst;

	for (size_t i{ 0 }; i < length >> 1; ++i)
	{
		inst = reinterpret_cast<uint16_t*>(contents)[i];
	}

	delete[] mem;
}
