#ifndef UTILITY_H
#define UTILITY_H

#include <map>

enum class Keyword
{
	ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR // opcode
};

// function class for maps containing strings
class StrLess
{
public:
	bool operator()(const char* a, const char* b) const;
};

// keywords mapped to the Keyword enum class
extern const std::map<const char*, Keyword, StrLess> keywords;

#endif // UTILITY_H
