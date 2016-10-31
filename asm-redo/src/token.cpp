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
		break;

	case END:
		return "end";
		break;

	case NEWLINE:
		return "newline";
		break;

	case KEYWORD:
		return "keyword";
		break;

	case LABEL:
		return "label";
		break;

	case REGISTER:
		return "register";
		break;

	case IMMEDIATE:
		return "immediate";
		break;

	case IDENTIFIER:
		return "identifier";
		break;

	case ERROR:
		return "error";
		break;

	default:
		return "NULL";
	}
}
