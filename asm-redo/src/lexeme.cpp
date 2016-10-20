#include "../inc/lexeme.h"

Lexeme::Lexeme(char* name, Category category)
	: name{ name }, category{ category } {}

const char* Lexeme::getName()
{
	return name;
}

Lexeme::Category Lexeme::getCategory()
{
	return category;
}
