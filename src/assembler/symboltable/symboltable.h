#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>	// for uint16_t
#include <vector>	// for std::vector

class Symbol
{
public:
	const char* name;
	uint16_t value;
};

class SymbolTable: public std::vector<Symbol>
{
public:
	// initializer list constructor
	SymbolTable(std::initializer_list<Symbol> list);

	// search for a symbol and add if not already in list, returning status
	bool resolve(const char* token);

	// search for a symbol and return a pointer to it
	Symbol* search(const char* token);
};

#endif // SYMBOLTABLE_H