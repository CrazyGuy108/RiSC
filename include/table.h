#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>         // for map
#include "exception.h" // for TokenException

class StrLess
{
public:
	bool operator()(const char* a, const char* b) const
	{
		return strcmp(a, b) < 0;
	}
};

template <typename T>
class Table
{
public:
	typedef T value_type;
	typedef std::map<const char*, value_type, StrLess> map_type;

	Table()
		: data{} {}

	Table(std::initializer_list<typename map_type::value_type> data)
		: data{ data } {}

	const value_type& operator[](const char* token) const
	{
		try
		{
			return data.at(token);
		}
		catch (...) // if the map access wasn't successful
		{
			throw TokenException{ token };
		}
	}

	// insert a value in order
	void insert(const char* name, value_type& value)
	{
		if(!data.insert(map_type::value_type{ name, value }).second) // couldn't insert, already defined
			throw SymbolException{ name };
	}

	typename map_type::iterator begin() noexcept
	{
		return data.begin();
	}

	typename map_type::const_iterator begin() const noexcept
	{
		return data.begin();
	}

	typename map_type::iterator end() noexcept
	{
		return data.end();
	}

	typename map_type::const_iterator end() const noexcept
	{
		return data.end();
	}

private:
	map_type data;
};

#endif // SYMBOLTABLE_H