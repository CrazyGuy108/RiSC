#include "../inc/generator.hpp"

Generator::Generator(Parser& parser)
	: errors{ 0 }
{
	generate(parser);
}

void Generator::generate(Parser& parser)
{

}

inst_t Generator::next()
{
	if (!empty())
	{
		inst_t tmp{ bytecode.front() };
		bytecode.pop();
		return tmp;
	}
	else
		return 0; // create a nop
}

bool Generator::empty() const
{
	return bytecode.empty();
}

size_t Generator::getErrors() const
{
	return errors;
}

const symbol_table& Generator::getSymbolTable() const
{
	return symtable;
}
