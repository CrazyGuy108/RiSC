#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <map>         // for map
#include "lexeme.hpp"  // for Lexeme
#include "utility.hpp" // for inst_t

// container adaptor for mapping Lexemes onto inst_t's
class SymbolTable final
{
public:
	typedef std::map<Lexeme, inst_t>         map_type;
	typedef map_type::value_type             value_type;
	typedef map_type::iterator               iterator;
	typedef map_type::reverse_iterator       reverse_iterator;
	typedef map_type::const_iterator         const_iterator;
	typedef map_type::const_reverse_iterator const_reverse_iterator;

	SymbolTable() = default;
	SymbolTable(std::initializer_list<value_type> il);

private:
	map_type symbols;
};

#endif // SYMBOLTABLE_HPP
