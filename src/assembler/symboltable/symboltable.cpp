#include "symboltable.h"

Symbol::Symbol(const char* name, uint16_t value)
	: name{ name }, value{ value } {}

int SymbolTable::search(const char* token)
{
	// performs a binary search

	size_type start{ 0 };			// start index
	size_type end{ size() - 1 };	// end index
	size_type middle;				// index to test
	int comparison;					// temp output of strcmp

	do
	{
		middle = (start + end) >> 1;	// average with shift optimization
		comparison = cmp(at(middle).name, token);

		if (comparison < 0)			// <
			start = middle + 1;
		else if (comparison > 0)	// >
			end = middle - 1;
		else						// =
			return middle;
	} while (start <= end);

	return -1;
}

int cmp(const char* a, const char* b)
{
	// go through every character and compare them
	// stop AFTER comparing the null terminator, not before like in strcmp
	size_t index{ 0 };
	do
	{
		if (a[index] < b[index])
			return -1;
		else if (a[index] > b[index])
			return 1;
		else
			++index;
	}
	while (a[index] && b[index]);

	return 0;
}