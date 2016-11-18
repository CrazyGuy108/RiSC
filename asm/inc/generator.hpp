#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <utility>     // for pair
#include <vector>      // for vector
#include "parser.hpp"  // for Parser
#include "utility.hpp" // for inst_t

class Generator
{
public:
	typedef std::map<Lexeme, inst_t> symbol_table;
	typedef std::vector<inst_t>      bytecode_list;

	Generator() = default;
	Generator(Parser& parser);

	void generate(Parser& parser);
	inst_t next();
	bool empty() const;
	size_t getErrors() const;
	const symbol_table& getSymbolTable() const;

private:
	bytecode_list bytecode;           // stream of bytecode
	bytecode_list::const_iterator it; // keeps track of position
	size_t errors;                    // amount of errors encountered
	symbol_table symtable;            // table for resolving labels
};

#endif // GENERATOR_HPP
