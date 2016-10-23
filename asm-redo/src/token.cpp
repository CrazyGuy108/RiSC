#include "../inc/token.h"

Token::Token(char* name, Type type)
	: name{ name }, type{ type } {}

const char* Token::getName()
{
	return name != nullptr ? name
	                       : "NULL";
}

Token::Type Token::getType()
{
	return type;
}

const char* Token::getTypeName()
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
