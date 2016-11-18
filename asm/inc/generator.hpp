#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <queue>       // for queue
#include "parser.hpp"  // for Parser
#include "utility.hpp" // for inst_t

class Generator
{
public:
	Generator() = default;
	Generator(Parser& parser);

	void generate(Parser& parser);
	inst_t next();
	bool empty() const;
	size_t getErrors() const;
	const symbol_table& getSymbolTable() const;

private:
	std::queue<inst_t> bytecode;
	size_t errors;
	symbol_table symtable;
};

#endif // GENERATOR_HPP
