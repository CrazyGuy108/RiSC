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
	if (argc == 3)
	{
		uint16_t immed{ imm(argv[2]) };
		if (immed & 0xffc0 == immed) // use only lui
		{
			thisptr->instructions = new Instruction[1]
			{
				Instruction{ { LUI, OpType::RI }, new RI{ argv[1], argv[2] }, 2 }
			};

			thisptr->length = 1;
		}
		else if(immed & 0x003f == immed) // use only lli
		{
			thisptr->instructions = new Instruction[1]
			{
				Instruction{ { ADDI, OpType::RRI }, new RRI{ argv[1], argv[1], argv[2] }, 3 }
			};

			thisptr->length = 1;
		}
		else // use both lui and lli
		{
			thisptr->instructions = new Instruction[2]
			{
				Instruction{ { LUI, OpType::RI }, new RI{ argv[1], argv[2] }, 2 }, // lui
				Instruction{ { ADDI, OpType::RRI }, new RRI{ argv[1], argv[1], argv[2] }, 3 } // lli
			};

			thisptr->length = 2;
		}
	}
	else
		; // error: operand count does not match
}

void fill(Line* thisptr, size_t argc, const char** argv)
{
	// immediate replaces the entire instruction
}

void space(Line* thisptr, size_t argc, const char** argv)
{

}