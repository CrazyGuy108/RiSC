#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>			// for uint16_t
#include <vector>			// for std::vector

class Symbol
{
public:
	Symbol(const char* name, uint16_t value);

	const char* name;
	uint16_t value;
};

class SymbolTable
{
public:
	SymbolTable(std::initializer_list<Symbol> list);

	size_t size();

	// without bounds checking
	Symbol& operator[](size_t index);
	Symbol& operator[](const char* token);

	// with bounds checking
	Symbol& at(size_t index);
	Symbol& at(const char* token);

private:
	std::vector<Symbol> data;

	// binary search for a Symbol's index
	size_t search(const char* token);
};

extern SymbolTable table;

#endif // SYMBOLTABLE_H