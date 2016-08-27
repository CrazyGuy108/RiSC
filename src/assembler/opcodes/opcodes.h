#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include "../symboltable/symboltable.h"

// opcode class
	// contains opcode number and inst. type(rrr, rri, ri probs enum/macro)
// in some other file make pseudo op class
	// gives data + conditional compilation(if needed) for how to translate

class Opcode
{
public:
	Opcode(uint16_t opcode);

	uint16_t opcode;
};

class RRR
{

};

class Add
	: public Opcode, public RRR
{

};

#endif // OPCODES_H