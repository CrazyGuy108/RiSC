#ifndef WRITE_H
#define WRITE_H

#include "memory.h"    // for Memory
#include "utilities.h" // for typedefs

// stores data on what should be written to memory
class Write
	: public Memory
{
public:
	Write(MemUnit unit, size_t addr, uword_t value);

	uword_t value; // value to be written
};

#endif // WRITE_H
