#include "symboltable.h"

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