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

template <typename T>
class SymbolTable: public std::vector<T>
{

};

#endif // SYMBOLTABLE_H