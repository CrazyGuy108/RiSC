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

bool Lexer::isLabelName(const char* name)
{
	return name[strlen(name) - 1] == ':';
}

bool Lexer::isRegName(const char* name)
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

bool Lexer::isImmName(const char* name)
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

Lexeme::Category Lexer::formatLabel(char* name)
{
	name[strlen(name) - 1] = '\0'; // remove colon
	return name[0] == '.' ? Lexeme::LOCAL_LABEL
	                      : Lexeme::LABEL;
}

Lexeme::Category Lexer::formatReg(char* name)
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

Lexeme::Category Lexer::formatImm(char* name)
{
	return Lexeme::IMMEDIATE;
}

Lexeme::Category Lexer::formatKeyword(char* name)
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
