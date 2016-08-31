#ifndef PSEUDO_H
#define PSEUDO_H

// prototypes
enum class Pseudo;
class PseudoInstruction;

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
	PseudoInstruction(size_t length);

	// dynamically allocated array of Instructions
	// expected to be constructed and destructed by Line
	Instruction* translation;
	size_t length;
};

class Nop
	: public PseudoInstruction
{
public:
	// translates into "add 0 0 0"
	Nop();
};

#endif // PSEUDO_H