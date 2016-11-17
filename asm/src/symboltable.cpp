#include "../inc/symboltable.hpp"

SymbolTable::SymbolTable(std::initializer_list<map_type::value_type> il)
	: symbols{ il } {}
