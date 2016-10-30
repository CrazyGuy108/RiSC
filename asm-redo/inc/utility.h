#ifndef UTILITY_H
#define UTILITY_H

#include <map>

enum class Keyword
{
	ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR // opcode
};

class StrLess
{
public:
	bool operator()(const char* a, const char* b) const;
};

extern const std::map<const char*, Keyword, StrLess> keywords;

#endif // UTILITY_H
