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
	typedef map_type::const_iterator         const_iterator;

	SymbolTable() = default;
	SymbolTable(std::initializer_list<value_type> il);

	void add(const Lexeme& lexeme, inst_t value);  // creates an entry
	inst_t operator[](const Lexeme& lexeme) const; // finds an entry
	bool empty() const; // check if there are no entries

	// iterator functions

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

private:
	map_type symbols;
};

#endif // SYMBOLTABLE_HPP
