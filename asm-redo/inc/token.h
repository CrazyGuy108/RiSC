#ifndef TOKEN_H
#define TOKEN_H

#include "lexeme.h" // for Lexeme

// defines a token containing a name and a type
class Token
{
public:
	enum Type
	{
		BEGIN, END, NEWLINE, // punctuation
		KEYWORD, LABEL, REGISTER, IMMEDIATE, IDENTIFIER, // type of lexeme
		ERROR // lexical error
	};

	Token() = default;
	Token(char* name, Type type);

	const char* getName();
	Type getType();
	const char* getTypeName();

private:
	char* name; // aka lexeme
	//Lexeme lexeme;
	Type type;
};

#endif // TOKEN_H
