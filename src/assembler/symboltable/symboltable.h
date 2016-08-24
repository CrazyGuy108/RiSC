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

	// search for a symbol and add if nonexistent
	// returns true if the token is not already registered
	bool resolve(const char* token);

	// binary search for a symbol
	// returns nullptr if not found so be careful
	Symbol* search(const char* token);
};

#endif // SYMBOLTABLE_H