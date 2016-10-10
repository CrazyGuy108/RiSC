#ifndef WRITE_H
#define WRITE_H

#include <cstdint>  // for uint16_t
#include "memory.h" // for Memory

// stores data on what should be written to memory
class Write
	: public Memory
{
public:
	Write(MemUnit unit, size_t addr, uint16_t value);

	uint16_t value; // value to be written
};

#endif // WRITE_H
