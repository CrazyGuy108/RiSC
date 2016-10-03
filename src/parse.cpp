#include "../include/parse.h"

inst_t reg(const char* name)
{
	static const Table<inst_t> regs
	{
		{ "r0",	0x0000 },
		{ "r1",	0x0001 },
		{ "r2",	0x0002 },
		{ "r3",	0x0003 },
		{ "r4",	0x0004 },
		{ "r5",	0x0005 },
		{ "r6",	0x0006 },
		{ "r7",	0x0007 }
	};

	return regs[name];
}

inst_t imm(const char* name)
{
	char* endp;
	long value{ strtol(name, &endp, 0) };

	return endp == name ? symbols[name] : (inst_t)value;
}

void compile(const std::vector<std::vector<char*>>& words, const std::vector<Opcode>& opcodes)
{
	unsigned int errors{ 0 };

	line_t bytecode;
	line_t tmp;
	size_t line{ 0 };

	for (size_t i{ 0 }; i < words.size(); ++i)
	{
		std::cout << "compiling line " << i << "...\n";

		try
		{
			tmp = opcodes[i].getFunc()(words[i].size(), (const char**)words[i].data(), line);
			bytecode.insert(bytecode.end(), tmp.begin(), tmp.end());
			line += opcodes[i].length(); // some instructions take multiple instruction words when compiled
		}
		catch (TokenException e)
		{
			std::cout << "error in line " << i << ": unresolved symbol \"" << e.what() << "\"\n";
			++line;
			++errors;
		}
		catch (OperandException e)
		{
			std::cout << "error in line " << i << ": opcode \"" << e.what() << "\" expected " << e.getExpected() << " operands but was given " << e.getGiven() << " instead\n";
			++line;
			++errors;
		}

	}
}