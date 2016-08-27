#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>	// for uint16_t
#include <vector>	// for std::vector

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

	// binary search for a Symbol's index
	int search(const char* token);

private:
	std::vector<Symbol> data;
};

// string comparison that includes the null character unlike strcmp
// e.g. strcmp("a","ab")=0, cmp("a","ab")=-1
int cmp(const char* a, const char* b);

/***** move to a separate file later *****/
extern SymbolTable opcodes;
extern SymbolTable regs;
extern SymbolTable imms;	/***** create class/function instead of this *****/
extern SymbolTable symbols;

#endif // SYMBOLTABLE_H