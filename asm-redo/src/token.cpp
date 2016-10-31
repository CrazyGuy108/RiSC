#include "../inc/token.h"

std::ostream& operator<<(std::ostream& os, const Token& t)
{
	return os << t.lexeme << ": " << t.getTypeName();
}

Token::Token(char* name, Type type)
	: name{ name }, type{ type } {}

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
