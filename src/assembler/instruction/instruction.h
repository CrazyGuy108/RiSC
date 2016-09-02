#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// prototypes
class Line;

#include <cstdint>
#include "../utilities/utilities.h"

class Line
{
public:
	Line(uint16_t* instructions, size_t length);
	~Line();

	// array of compiled instructions
	uint16_t* instructions;

	// keeps track of how many Instructions
	size_t length;
};

// takes in a parsed line of code to produce a series of bytecode instructions
Line compile(size_t argc, const char** argv);

#endif // INSTRUCTION_H