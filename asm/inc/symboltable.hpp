#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <map>         // for map
#include "lexeme.hpp"  // for Lexeme
#include "utility.hpp" // for inst_t

// container adaptor for mapping Lexemes onto inst_t's
class SymbolTable final
{
public:
	typedef std::map<Lexeme, inst_t> map_type;

	SymbolTable(std::initializer_list<map_type::value_type> il);

private:
	map_type symbols;
};

#endif // SYMBOLTABLE_HPP
