#ifndef RESULT_H
#define RESULT_H

#include <cstdint> // for uint16_t

// stores data on what should be committed to registers
class Result
{
public:
	// specifies what memory unit to write to
	enum Dest
	{
		REGISTERS, MEMORY
	};

	Result(uint16_t id, uint16_t value, Dest dest);

	uint16_t id, value;
	Dest dest;
};

#endif // RESULT_H
