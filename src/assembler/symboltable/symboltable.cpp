#include "symboltable.h"

Symbol::Symbol(const char* name, uint16_t value)
	: name{ name }, value{ value } {}

SymbolTable::SymbolTable(std::initializer_list<Symbol> data)
	: data{ data } {}

size_t SymbolTable::size()
{
	return data.size();
}

Symbol& SymbolTable::operator[](size_t index)
{
	return data[index];
}

Symbol& SymbolTable::operator[](const char* token)
{
	return data[search(token)];
}

Symbol& SymbolTable::at(size_t index)
{
	if (index < size())
		return operator[](index);
	else
		abort();
}

Symbol& SymbolTable::at(const char* token)
{
	int index{ search(token) };
	if (index != -1)
		return data[index];
	else
		abort();
}

int SymbolTable::search(const char* token)
{
	size_t start{ 0 };
	size_t end{ size() - 1 };
	size_t middle;
	int comparison;

	do
	{
		middle = (start + end) >> 1;
		comparison = cmp(data[middle].name, token);

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

SymbolTable opcodes
{
	{ "add",	0x0000 },
	{ "addi",	0x2000 },
	{ "beq",	0xC000 },
	{ "jalr",	0xE000 },
	{ "lui",	0x6000 },
	{ "lw",		0xA000 },
	{ "nand",	0x4000 },
	{ "sw",		0x8000 }
};

SymbolTable regs
{
	{ "0",	0x0000 },
	{ "1",	0x0001 },
	{ "2",	0x0002 },
	{ "3",	0x0003 },
	{ "4",	0x0004 },
	{ "5",	0x0005 },
	{ "6",	0x0006 },
	{ "7",	0x0007 },
	{ "r0", 0x0000 },
	{ "r1", 0x0001 },
	{ "r2", 0x0002 },
	{ "r3", 0x0003 },
	{ "r4", 0x0004 },
	{ "r5", 0x0005 },
	{ "r6", 0x0006 },
	{ "r7", 0x0007 }
};