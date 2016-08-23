#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>	// for uint16_t
#include <vector>	// for std::vector

class Symbol
{
public:
	char* name;
	uint16_t value;
};

class SymbolTable: public std::vector<Symbol>
{

};

#endif // SYMBOLTABLE_H