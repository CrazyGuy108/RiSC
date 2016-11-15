#include "../inc/token.hpp"

std::ostream& operator<<(std::ostream& os, const Token& t)
{
	return os << t.lexeme << ": " << t.getTypeName();
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

const char* Token::getTypeName() const
{
	switch (type)
	{
	case BEGIN:
		return "begin";

	case END:
		return "end";

	case NEWLINE:
		return "newline";

	case KEYWORD:
		return "keyword";

	case LABEL:
		return "label";

	case REGISTER:
		return "register";

	case IMMEDIATE:
		return "immediate";

	case IDENTIFIER:
		return "identifier";

	case ERROR:
		return "error";

	default:
		return "NULL";
	}
}
