#include "../inc/generator.hpp"

Generator::Generator(Parser& parser)
	: errors{ 0 }
{
	generate(parser);
}

void Generator::generate(Parser& parser)
{
	// generate code
	it = bytecode.cbegin();
}

inst_t Generator::next()
{
	return *it++;
}

bool Generator::empty() const
{
	return it == bytecode.cend();
}

size_t Generator::getErrors() const
{
	return errors;
}

const Generator::symbol_table& Generator::getSymbolTable() const
{
	return symtable;
}
