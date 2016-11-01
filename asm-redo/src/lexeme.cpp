#include "../inc/lexeme.h"

std::ostream& operator<<(std::ostream& os, const Lexeme& l)
{
	if(l.beg == nullptr || l.end == nullptr)
		return os << "NULL";

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

bool operator<(const Lexeme& l, const Lexeme& r)
{
	return l.cmp(r) < 0;
}

int Lexeme::cmp(const Lexeme& l)
{
	size_t i{ 0 };
	while (&beg[i] != end && &l.beg[i] != l.end)
		if (beg[i] < l.beg[i])
			return -1; // <
		else if (beg[i] > l.beg[i])
			return 1; // >
		else
			++i;

	return 0; // =
}

Lexeme::Lexeme(const char* ptr)
	: Lexeme{ ptr, ptr } {}

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

void Lexeme::setBeg(const char* beg)
{
	this->beg = beg;
}

void Lexeme::setEnd(const char* end)
{
	this->end = end;
}

size_t Lexeme::length() const
{
	return end - beg;
}
