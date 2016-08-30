#ifndef PSEUDO_H
#define PSEUDO_H

#include "../instruction/instruction.h"

enum class Pseudo
{
	NOP,
	HALT,
	LLI,
	MOVI,
	FILL,
	SPACE
};

class PseudoInstruction
{
public:
	Instruction* translation;
};

// abstract example
class Nop
	: public PseudoInstruction
{
public:
	// takes no arguments of course
	// translates into "add 0 0 0"
	Nop();
};

#endif // PSEUDO_H