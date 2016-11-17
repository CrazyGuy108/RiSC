#include "../inc/symboltable.hpp"

SymbolTable::SymbolTable(std::initializer_list<value_type> il)
	: symbols{ il } {}
