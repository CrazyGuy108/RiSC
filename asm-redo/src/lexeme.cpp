#include "../inc/lexeme.h"

std::ostream& operator<<(std::ostream& os, const Lexeme& l)
{
	size_t len{ l.length() };
	char* str{ new char[len + 1] };

	// copy Lexeme into char array
	for (size_t i{ 0 }; i < len; ++i)
		str[i] = l.beg[i];
	str[len] = '\0'; // terminate copy

	os << str;
	delete[] str;
	return os;
}

Lexeme::Lexeme(const char* beg, const char* end)
	: beg{ beg }, end{ end } {}

const char* Lexeme::getBeg() const
{
	return beg;
}

const char* Lexeme::getEnd() const
{
	return end;
}

size_t Lexeme::length() const
{
	return beg < end ? end - beg
	                 : beg - end;
}
