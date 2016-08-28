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

template <typename T>
class Symbol
{
public:
	Symbol(const char* name, T& value)
		: name{ name }, value{ value } {}

	const char* name;
	T value;
};

template <typename T>
class Table
{
public:
	typedef Symbol<T> symbol_type;

	Table(std::initializer_list<symbol_type> data)
		: data{ data } {}

	size_t size()
	{
		return data.size();
	}

	T& operator[](size_t index)
	{
		return data[index];
	}

	T& operator[](const char* token)
	{
		return data[search(token)];
	}

	T& at(size_t index)
	{
		if (index < size())
			return operator[](index);
		else
			abort();
	}

	T& at(const char* token)
	{
		int index{ search(token) };
		if (index != -1)
			return operator[](index);
		else
			abort();
	}

	// binary search for a Symbol's index
	int search(const char* token)
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

private:
	std::vector<symbol_type> data;
};

// string comparison that includes the null character unlike strcmp
// e.g. strcmp("a","ab")=0, cmp("a","ab")=-1
int cmp(const char* a, const char* b);

/***** move to a separate file later *****/
typedef Table<uint16_t> SymbolTable;

extern SymbolTable opcodes;
extern SymbolTable regs;
extern SymbolTable imms;	/***** create class/function instead of this *****/
extern SymbolTable symbols;

#endif // SYMBOLTABLE_H