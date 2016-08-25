#include "symboltable.h"

Symbol::Symbol(const char* name, uint16_t value)
	: name{ name }, value{ value } {}

SymbolTable::size_type SymbolTable::search(const char* token)
{
	// performs a uniform binary search

	size_type start{ 0 };			// start index
	size_type end{ size() - 1 };	// end index
	size_type middle;				// index to test
	int comparison;					// temp output of strcmp

	do
	{
		middle = (start + end) >> 1;	// average with shift optimization
		comparison = strcmp(at(middle).name, token);

		if (comparison < 0)			// <
			start = middle + 1;
		else if (comparison > 0)	// >
			end = middle - 1;
		else						// =
			return middle;
	} while (start <= end);

	return -1;
}