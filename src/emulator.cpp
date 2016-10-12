#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	RiSC machine;

	for (size_t i{ 0 }; i < length; ++i)
		if (i % 2)
			machine.execute(((inst_t)contents[i - 1] << 8) | (inst_t)contents[i]);
}
