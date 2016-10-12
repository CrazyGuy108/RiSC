#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	RiSC machine;

	for (size_t i{ 0 }; i < length >> 1; ++i)
	{
		machine.execute(((inst_t*)contents)[i]);
	}
}
