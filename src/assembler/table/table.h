#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <cstdint>	// for uint16_t
#include <vector>	// for std::vector

template <typename T>
class Item
{
public:
	typedef T value_type;

	Item(const char* name, value_type value)
		: name{ name }, value{ value } {}

	Item(const char* name, value_type& value)
		: name{ name }, value{ value } {}

	const char* name;
	value_type value;
};

template <typename T>
class Table
{
public:
	typedef Item<T> item_type;
	typedef T value_type;

	Table()
		: data{} {}

	Table(std::initializer_list<item_type> data)
		: data{ data } {}

	size_t size()
	{
		return data.size();
	}

	value_type& operator[](size_t index)
	{
		return data[index].value;
	}

	value_type& operator[](const char* token)
	{
		return at(token);
	}

	value_type& at(size_t index)
	{
		if (index < size())
			return operator[](index);
		else
			abort();
	}

	value_type& at(const char* token)
	{
		int index{ search(token) };
		if (index > 0)
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
	std::vector<item_type> data;
};

#endif // SYMBOLTABLE_H