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
		{}

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
		int index{ closestMatch(token) };
		if (index != -1 && cmp(data[index].name, token) != -1)
			return index;
		else
			return -1;
	}

	// insert a value in order
	void insert(const char* name, value_type& value)
	{
		int index{ closestMatch(name) };
		if (index != -1 && cmp(data[index].name, name) != -1)
			; // error: already defined
		else
			data.insert(data.begin() + index, item_type{ name, value });
	}

private:
	std::vector<item_type> data;

	// binary search for the closest match to an item
	// used by insert and search
	int closestMatch(const char* token)
	{
		if (token == nullptr)
			return -1;

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

		return middle;
	}
};

#endif // SYMBOLTABLE_H