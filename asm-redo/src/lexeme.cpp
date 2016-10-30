#include "../inc/lexeme.h"

Lexeme::Lexeme(const char* beg, const char* end)
	: beg{ beg }, end{ end } {}

const char* Lexeme::getBeg()
{
	return beg;
}

const char* Lexeme::getEnd()
{
	return end;
}
