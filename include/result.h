#ifndef RESULT_H
#define RESULT_H

#include <cstdint> // for uint16_t

// stores data on what should be committed to registers
class Result
{
public:
	Result(uint16_t regID, uint16_t value);

	uint16_t regID, value;
};

#endif // RESULT_H
