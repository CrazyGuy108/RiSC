#include "../inc/symboltable.hpp"

SymbolTable::SymbolTable(std::initializer_list<value_type> il)
	: symbols{ il } {}

void SymbolTable::add(const Lexeme& lexeme, inst_t value)
{
	symbols.emplace(lexeme, value);
}

inst_t SymbolTable::operator[](const Lexeme& lexeme) const
{
	return symbols.at(lexeme);
}

bool SymbolTable::empty() const
{
	return symbols.empty();
}


SymbolTable::iterator SymbolTable::begin()
{
	return symbols.begin();
}

SymbolTable::const_iterator SymbolTable::begin() const
{
	return symbols.cbegin();
}

SymbolTable::const_iterator SymbolTable::cbegin() const
{
	return symbols.cbegin();
}

SymbolTable::iterator SymbolTable::end()
{
	return symbols.end();
}

SymbolTable::const_iterator SymbolTable::end() const
{
	return symbols.cend();
}

SymbolTable::const_iterator SymbolTable::cend() const
{
	return symbols.cend();
}
