#include "pseudo.h"

Line nop(size_t argc, const char** argv)
{
	// translates from "nop" to "add 0 0 0"
	if (argc == 1)
	{
		
	}
	else
		; // error: operand count does not match
}

Line halt(size_t argc, const char** argv)
{

}

Line lli(size_t argc, const char** argv)
{
	// translates from "lli rA, imm6" to "addi rA, rA, imm6"
	if (argc == 3)
	{
		
	}
	else
		; // error: operand count does not match
}

Line movi(size_t argc, const char** argv)
{
	if (argc == 3)
	{
		int16_t immed{ imm(argv[2]) };
		if (immed & 0xffc0 == immed) // use only lui
		{
			
		}
		else if(immed & 0x003f == immed) // use only lli
		{
			
		}
		else // use both lui and lli
		{
			
		}
	}
	else
		; // error: operand count does not match
}

Line fill(size_t argc, const char** argv)
{
	// immediate replaces the entire instruction
	if (argc == 2)
	{
		
	}
	else
		; // error: operand count does not match
}

Line space(size_t argc, const char** argv)
{

}