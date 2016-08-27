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
	int search(const char* token);
};

// string comparison that includes the null character unlike strcmp
// strcmp("a","ab")=0 cmp("a","ab")=-1
int cmp(const char* a, const char* b);

extern SymbolTable table;

#endif // SYMBOLTABLE_H