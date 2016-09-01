#include "pseudo.h"

void nop(Line* thisptr, size_t argc, const char** argv)
{
	// translates from "nop" to "add 0 0 0"
	// no compiling step needed, so init with pre-compiled data
	if (argc == 1)
	{
		thisptr->instructions = new Instruction[1]
		{
			Instruction{ { ADD, OpType::RRR }, new RRR{ 0, 0, 0 }, 3 }
		};

		thisptr->length = 1;
	}
	else
		; // error: too many operands
}

void halt(Line* thisptr, size_t argc, const char** argv)
{

}

void lli(Line* thisptr, size_t argc, const char** argv)
{
	// translates from "lli rA, imm6" to "addi rA, rA, imm6"
	if (argc == 3)
	{
		thisptr->instructions = new Instruction[1]
		{
			Instruction{ { ADDI, OpType::RRI }, new RRI{ argv[1], argv[1], argv[2] }, 3 }
		};

		thisptr->length = 1;
	}
	else
		; // error: operand count does not match
}

void movi(Line* thisptr, size_t argc, const char** argv)
{

}

void fill(Line* thisptr, size_t argc, const char** argv)
{

}

void space(Line* thisptr, size_t argc, const char** argv)
{

}