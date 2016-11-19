#include "../inc/emulator.hpp"

void emulator(char* contents, size_t length)
{
	RiSC machine;
	machine.load(contents, length);
	machine.execute();
}
