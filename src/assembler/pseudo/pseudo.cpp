#include "pseudo.h"

void nop(Line* thisptr, size_t argc, const char** argv)
{
	// translates from "nop" to "add 0 0 0"
	if (argc == 1)
	{
		
	}
	else
		; // error: operand count does not match
}

void halt(Line* thisptr, size_t argc, const char** argv)
{

}

void lli(Line* thisptr, size_t argc, const char** argv)
{
	// translates from "lli rA, imm6" to "addi rA, rA, imm6"
	if (argc == 3)
	{
		
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

void fill(Line* thisptr, size_t argc, const char** argv)
{
	// immediate replaces the entire instruction
	if (argc == 2)
	{
		
	}
	else
		; // error: operand count does not match
}

void space(Line* thisptr, size_t argc, const char** argv)
{

}