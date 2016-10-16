#ifndef TABLE_H
#define TABLE_H

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
	typedef std::map<const char*, T, StrLess> map_type;
	typedef typename map_type::mapped_type    value_type;
	typedef typename map_type::iterator       iterator;
	typedef typename map_type::const_iterator const_iterator;

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
		if(!data.insert({ name, value }).second) // couldn't insert, already defined
			throw SymbolException{ name };
	}

	iterator begin() noexcept
	{
		return data.begin();
	}

	const_iterator begin() const noexcept
	{
		return data.begin();
	}

	iterator end() noexcept
	{
		return data.end();
	}

	const_iterator end() const noexcept
	{
		return data.end();
	}

private:
	map_type data;
};

#endif // TABLE_H
