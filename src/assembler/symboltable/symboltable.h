#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>	// for uint16_t
#include <vector>	// for std::vector

/***** move to a separate file later *****/
#define ADD 0x0000
#define ADDI 0x2000
#define NAND 0x4000
#define LUI 0x6000
#define SW 0x8000
#define LW 0xA000
#define BEQ 0xC000
#define JALR 0xE000

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