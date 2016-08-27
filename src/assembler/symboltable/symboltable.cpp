#include "symboltable.h"

constexpr Symbol::Symbol(const char* name, uint16_t value)
	: name{ name }, value{ value } {}

size_t SymbolTable::size()
{
	return data.size();
}