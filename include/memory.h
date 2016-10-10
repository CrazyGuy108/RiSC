#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
public:
	// specifies which memory unit should be accessed
	enum MemUnit
	{
		REGISTERS, RAM
	};

	Memory(MemUnit unit, size_t addr);

	MemUnit unit; // which memory unit to access
	size_t addr;  // address to be given to the memory unit
};

#endif // MEMORY_H
