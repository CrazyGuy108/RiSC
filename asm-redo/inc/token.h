#ifndef LEXEME_H
#define LEXEME_H

// defines a token containing a name and a type
class Token
{
public:
	enum Type
	{
		BEGIN, END, NEWLINE, // punctuation
		LABEL, LOCAL_LABEL, REGISTER, IMMEDIATE, IDENTIFIER, // type of lexeme
		ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR, // reserved word
		ERROR // lexical error
	};

	Token() = default;
	Token(char* name, Type type);

	const char* getName();
	Type getType();
	const char* getTypeName();

private:
	char* name; // aka lexeme
	Type type;
};

#endif // LEXEME_H