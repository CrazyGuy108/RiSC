#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>			// for uint16_t
#include <vector>			// for std::vector
#include "../table/table.h"	// for Table

class Symbol
{
public:
	// constructor
	Symbol(const char* name, uint16_t value);

	const char* name;
	uint16_t value;
};

class SymbolTable
	: public Table<Symbol, std::vector<Symbol>>
{
public:
	// vector of symbols to build during assemble-time
	std::vector<Symbol> data;
};

#endif // SYMBOLTABLE_H