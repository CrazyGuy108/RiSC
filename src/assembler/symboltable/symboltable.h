#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>	// for uint16_t
#include <vector>	// for std::vector

template <typename T>
class Symbol
{
public:
	Symbol(const char* name, T value)
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

	symbol_type& operator[](size_t index)
	{
		return data[index];
	}

	symbol_type& operator[](const char* token)
	{
		return data[search(token)];
	}

	symbol_type& at(size_t index)
	{
		if (index < size())
			return operator[](index);
		else
			abort();
	}

	symbol_type& at(const char* token)
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

#endif // SYMBOLTABLE_H