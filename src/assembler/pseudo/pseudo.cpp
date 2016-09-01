#include "pseudo.h"

void nop(Line* thisptr, size_t argc, const char** argv)
{
	// translates to "add 0 0 0"
	// no compiling step needed, so init with pre-compiled data

	thisptr->instructions = new Instruction[1]
	{
		Instruction{ { ADD, OpType::RRR }, new RRR{ 0, 0, 0 }, 3 }
	};

	thisptr->length = 1;
}

void halt(Line* thisptr, size_t argc, const char** argv)
{

}

void lli(Line* thisptr, size_t argc, const char** argv)
{

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