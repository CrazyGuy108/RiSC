#include "opcodes.h"

Line::Line(int argc, const char** argv)
{

}

Instruction::Instruction(int argc, const char** argv)
{
	if (argc >= 0)
	{
		int index{ opcodes.search(argv[0]) };
		if (index != -1)
			opcode = opcodes[index].value;
		else
			; // error: unresolved opcode
	}
	else
		; // no instruction given, must be a blank line then

	/***** wrap argc checks in instruction type check *****/

	// can only be RI
	if (argc >= 3)
		operands = new RI{ argv[1], argv[2] };
	else
		; // error: too few operands

	// could be RRR or RRI
	if (argc == 4)
	{
		// the only difference is the last operand, so check that first
		if (regs.search(argv[3]) != -1)
			operands = new RRR{ argv[1], argv[2], argv[3] };
		else
			operands = new RRI{ argv[1], argv[2], argv[3] };
	}
	else
		; // error: too many operands
}

Instruction::~Instruction()
{
	delete operands;
}