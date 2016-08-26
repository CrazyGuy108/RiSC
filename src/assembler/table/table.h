#ifndef TABLE_H
#define TABLE_H

template <typename T,	// data type
		  typename U>	// list type, must be either T* or a class operator[] overloaded
class Table
{
public:
	typedef T data_type;
	typedef U list_type;

	virtual size_t size() = 0;

	// access data by index
	data_type& operator[](size_t index)
	{
		return data[index];
	}

	// access data by name
	data_type& operator[](const char* token)
	{
		return data[search(token)];
	}

	// access data by index with bounds checking
	data_type& at(size_t index)
	{
		if (index < size())
			return operator[](index);
		else
			abort();
	}

	// access data by name with bounds checking
	data_type& at(const char* token)
	{
		size_t index{ search(token) };
		if (index >= 0)
			return data[index];
		else
			abort();
	}

protected:
	list_type data;

	size_t search(const char* token)
	{
		// performs a binary search

		size_t start{ 0 };			// start index
		size_t end{ size() - 1 };	// end index
		size_t middle;				// index to test

		do
		{
			middle = (start + end) >> 1;	// average with shift optimization
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
};

// cstring comparison
// stops AFTER comparing the null terminator, not before like in strcmp
int cmp(const char* a, const char* b);

#endif // TABLE_H