#include "../inc/token.hpp"

std::ostream& operator<<(std::ostream& os, const Token& t)
{
	return os << t.lexeme << ": " << getTypeName(t.type);
}

Token::Token(Type type)
	: lexeme{ "null" }, type{ type } {}

Token::Token(const Lexeme& lexeme, Type type)
	: lexeme{ lexeme }, type{ type } {}

const Lexeme& Token::getLexeme() const
{
	return lexeme;
}

Token::Type Token::getType() const
{
	return type;
}
