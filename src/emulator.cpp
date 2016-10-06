#include "../include/emulator.h"

void emulator(char* contents, size_t length)
{
	// if unaligned number of bytes, truncate
	if (length % 2)
		length -= 1;
}
