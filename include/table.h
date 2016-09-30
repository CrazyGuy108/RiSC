#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector> // for vector
#include "exception.h"

class TokenException
	: public RiscException
{
public:
	TokenException()
		: RiscException{} {}

	TokenException(const char* msg, const char* token)
		: RiscException{ msg }, token{ token } {}

protected:
	const char* token;
};

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
		: data{} {}

	Table(std::initializer_list<item_type> data)
		: data{ data } {}

	size_t size() const
	{
		return data.size();
	}

	const value_type& operator[](size_t index) const
	{
		return data[index].value;
	}

	const value_type& operator[](const char* token) const
	{
		return at(token);
	}

	const value_type& at(size_t index) const
	{
		if (index < size())
			return operator[](index);
		else
			abort();
	}

	const value_type& at(const char* token) const
	{
		int index{ search(token) };
		if (index > 0)
			return operator[](index);
		else
			throw TableException{ "unresolved token", token };
	}

	// binary search for a Symbol's index
	int search(const char* token) const
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
		if (index == -1) // check if invalid
			data.insert(data.begin(), item_type{ name, value }); // insert at start
		else if (cmp(data[index].name, name) != -1) // check if item already defined
			; // error: already defined
		else
			data.insert(data.begin() + index, item_type{ name, value });
	}

private:
	std::vector<item_type> data;

	// binary search for the closest match to an item
	// used by insert and search
	int closestMatch(const char* token) const
	{
		// prevent out of bounds errors
		if (data.empty())
			return -1;

		size_t start{ 0 };
		size_t end{ size() };
		size_t middle;
		int comparison;

		do
		{
			middle = (start + end) >> 1;
			comparison = cmp(data[middle].name, token);

			if (comparison < 0)      // <
				start = middle + 1;
			else if (comparison > 0) // >
				end = middle - 1;
			else                     // =
				return middle;
		} while (start <= end);

		return middle;
	}
};

#endif // SYMBOLTABLE_H