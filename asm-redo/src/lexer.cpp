#include "../inc/lexer.h"

Lexer::Lexer(char* iterator)
	: iterator{ iterator }, index{ 0 },
	  end{ false }, space{ true }, comment{ false },
	  lexemes{}
{
	lexemes.emplace(nullptr, Lexeme::BEGIN);
}

Lexeme Lexer::next()
{
	if(end)
		return Lexeme{ nullptr, Lexeme::END };
	else
	{
		// process the next token and return a new Lexeme
	}
}

Lexeme Lexer::tokenize(char* name)
{
	return Lexeme{ name,
		isLabelName(name) ? formatLabel(name)
		: isRegName(name) ? formatReg(name)
		: isImmName(name) ? formatImm(name)
		                  : formatKeyword(name) };
}

TOKEN_CHECK(Lexer::isLabelName)
{
	return name[strlen(name) - 1] == ':';
}

TOKEN_CHECK(Lexer::isRegName)
{
	// BEHOLD the almighty unmaintainable short-circuit evaluation behemoth!
	// now with spaces and comments so it doesn't hurt your eyes as much
	size_t len{ strlen(name) };
	return (len == 1 &&          // digit start
	        (name[0] >= '0' &&
	         name[0] <= '7')) || // digit end
	       (len == 2 &&          // r+digit start or digit+comma start
	        (name[0] == 'r' &&
	         name[1] >= '0' &&
	         name[1] <= '7') ||  // r+digit end
	        (name[0] >= '0' &&
	         name[0] <= '7' &&
	         name[1] == ',')) || // digit+comma end
	       (len == 3 &&          // r+digit+comma start
	        (name[0] == 'r' &&
	         name[1] >= '0' &&
	         name[1] <= '7' &&
	         name[2] == ','));   // r+digit+comma end
}

TOKEN_CHECK(Lexer::isImmName)
{
	size_t len{ strlen(name) };
	return (len >= 1 && // digit start
	        (name[0] >= '0' &&
	         name[0] <= '9')) || // digit end
	       (len >= 2 && // sign+digit start
	        (name[0] == '-' &&
	         name[1] >= '0' &&
	         name[2] <= '9')); // sign+digit end
}

TOKEN_FORMAT(Lexer::formatLabel)
{
	name[strlen(name) - 1] = '\0'; // remove colon
	return name[0] == '.' ? Lexeme::LOCAL_LABEL
	                      : Lexeme::LABEL;
}

TOKEN_FORMAT(Lexer::formatReg)
{
	if (name[0] == 'r') // remove optional r
	{
		name[0] = name[1];
		name[1] = '\0'; // implicitly also ignores the comma
	}
	else if (name[1] == ',') // remove optional comma
		name[1] = '\0';
	
	return Lexeme::REGISTER;
}

TOKEN_FORMAT(Lexer::formatImm)
{
	return Lexeme::IMMEDIATE;
}

TOKEN_FORMAT(Lexer::formatKeyword)
{
	return !strcmp(name, "add")  ? Lexeme::ADD
	     : !strcmp(name, "addi") ? Lexeme::ADDI
	     : !strcmp(name, "nand") ? Lexeme::NAND
	     : !strcmp(name, "lui")  ? Lexeme::LUI
	     : !strcmp(name, "sw")   ? Lexeme::SW
	     : !strcmp(name, "lw")   ? Lexeme::LW
	     : !strcmp(name, "beq")  ? Lexeme::BEQ
	     : !strcmp(name, "jalr") ? Lexeme::JALR
	                             : Lexeme::IDENTIFIER;
}
