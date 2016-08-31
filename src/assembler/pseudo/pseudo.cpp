#include "pseudo.h"

PseudoInstruction::PseudoInstruction(size_t length)
	: length{ length } {}

Nop::Nop()
	: PseudoInstruction{ 1 }
{
	translation = new Instruction[1]
	{
		Instruction
		{
			Opcode{ ADD, OpType::RRR },
			new RRR{ "0", "0", "0" },
			1
		}
	};
}