#include "symboltable.h"

Symbol::Symbol(const char* name, uint16_t value)
	: name{ name }, value{ value } {}

bool SymbolTable::resolve(const char* token)
{
	return false;	// placeholder
}

Symbol* SymbolTable::search(const char* token)
{
	// performs a uniform binary search

	size_type start{ 0 };			// start index
	size_type end{ size() - 1 };	// end index
	size_type middle;				// index to test
	int comparison;					// temp value to compare strings
	Symbol* dataptr{ nullptr };		// symbol to compare with token

	do
	{
		middle = (start + end) >> 1;	// average with shift optimization
		dataptr = &(at(middle));
		comparison = strcmp(dataptr->name, token);

		if (comparison < 0)			// data<token
			start = middle + 1;
		else if (comparison > 0)	// data>token
			end = middle - 1;
		else						// data=token
			return dataptr;
	} while (start <= end);

	return nullptr;
}