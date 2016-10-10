#ifndef READ_H
#define READ_H

#include "memory.h" // for Memory

// stores data on what should be read from memory
class Read
	: public Memory
{
public:
	Read(MemUnit unit, size_t addr);
};

#endif // READ_H
