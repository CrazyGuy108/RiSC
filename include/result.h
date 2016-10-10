#ifndef RESULT_H
#define RESULT_H

#include <cstdint>  // for uint16_t
#include "memory.h" // for Memory

// stores data on what should be committed to memory
class Result
	: public Memory
{
public:
	Result(MemUnit unit, size_t addr, uint16_t value);

	uint16_t value; // value to be written
};

#endif // RESULT_H
