#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>	// for uint16_t
#include <vector>	// for std::vector

class Symbol
{
public:
	// constructor
	Symbol(const char* name, uint16_t value);

	const char* name;
	uint16_t value;
};

class SymbolTable: public std::vector<Symbol>
{
public:
	// inherit vector's constructors
	using std::vector<Symbol>::vector;

	// binary search for a symbol
	size_type search(const char* token);
};

#endif // SYMBOLTABLE_H