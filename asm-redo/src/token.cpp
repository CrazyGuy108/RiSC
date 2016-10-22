#include "../inc/token.h"

Token::Token(char* name, Category category)
	: name{ name }, category{ category } {}

const char* Token::getName()
{
	return name != nullptr ? name
	                       : "NULL";
}

Token::Category Token::getCategory()
{
	return category;
}

const char* Token::getCategoryName()
{
	switch (category)
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

	case LABEL:
		return "label";
		break;

	case LOCAL_LABEL:
		return "local label";
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

	case ADD:
		return "add";
		break;

	case ADDI:
		return "addi";
		break;

	case NAND:
		return "nand";
		break;

	case LUI:
		return "lui";
		break;

	case SW:
		return "sw";
		break;

	case LW:
		return "lw";
		break;

	case BEQ:
		return "beq";
		break;

	case JALR:
		return "jalr";
		break;

	default:
		return "error";
	}
}
