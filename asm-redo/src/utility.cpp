#include "../inc/utility.h"

bool StrLess::operator()(const char* a, const char* b) const
{
	return strcmp(a, b) < 0;
}

const keyword_map keywords
{
	{ "add",  Keyword::ADD },
	{ "addi", Keyword::ADDI },
	{ "nand", Keyword::NAND },
	{ "lui",  Keyword::LUI },
	{ "sw",   Keyword::SW },
	{ "lw",   Keyword::LW },
	{ "beq",  Keyword::BEQ },
	{ "jalr", Keyword::JALR }
};
