#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	uint16_t inst;

	for (size_t i{ 0 }; i < length >> 1; ++i)
	{
		inst = reinterpret_cast<uint16_t*>(contents)[i];
	}
}
