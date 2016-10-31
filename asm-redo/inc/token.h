#ifndef TOKEN_H
#define TOKEN_H

#include "lexeme.h" // for Lexeme

// defines a token containing a name and a type
class Token
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Token& t);

	enum Type
	{
		BEGIN, END, NEWLINE, // punctuation
		KEYWORD, LABEL, REGISTER, IMMEDIATE, IDENTIFIER, // type of lexeme
		ERROR // lexical error
	};

	Token() = default;
	Token(const Lexeme& l, Type type);

	const char* getTypeName() const;

private:
	Lexeme lexeme;
	Type type;
};

#endif // TOKEN_H
