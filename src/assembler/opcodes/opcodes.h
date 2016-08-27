#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include "../symboltable/symboltable.h"

// opcode class
	// contains opcode number and inst. type(rrr, rri, ri probs enum/macro)
// in some other file make pseudo op class
	// gives data + conditional compilation(if needed) for how to translate

class Reg
{
public:
	Reg(const char* name);
	uint16_t value;
};

class RRR
{

};

uint16_t add(RRR& operands)
{

}

#endif // OPCODES_H