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

// compare 2 strings
// compare result with 0 to get comparison result
// i.e. -1(returned from cmp) is < because -1<0
// strcmp("a","ab") returns 0(=) for me so I had to rewrite it here
int cmp(const char* a, const char* b);

#endif // SYMBOLTABLE_H