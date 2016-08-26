#ifndef OPERANDS_H
#define OPERANDS_H

#include <cstdint>
#include <array>
#include "../symboltable/symboltable.h"

template<size_t length>
class RegTable
	: public Table<Symbol, Symbol*>
{
public:
	RegTable(Symbol* data)
		: data{ data } {}

	virtual size_t size()
	{
		return length;
	}
};

class Reg
{
public:
	Reg(const char* name);
	uint16_t value;
};

class Imm7
{
public:
	Imm7(const char* name);
	uint16_t value;
};

class Imm10
{
public:
	Imm10(const char* name);
	uint16_t value;
};

#endif // OPERANDS_H