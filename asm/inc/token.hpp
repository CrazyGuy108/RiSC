#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>   // for ostream
#include "lexeme.hpp" // for Lexeme

// defines a token containing a name and a type
class Token
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Token& t);

	enum Type
	{
		NEWLINE, // signal to the parser
		LABEL, REGISTER, IMMEDIATE, IDENTIFIER, // type of lexeme
		ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR, // opcode
		ERROR // lexical error
	};

	Token() = default;
	Token(Type type);
	Token(const Lexeme& lexeme, Type type);

	const Lexeme& getLexeme() const;
	Type getType() const;

private:
	Lexeme lexeme;
	Type type;
};

#include "utility.hpp" // for getTypeName

#endif // TOKEN_HPP
