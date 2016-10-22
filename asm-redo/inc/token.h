#ifndef LEXEME_H
#define LEXEME_H

// defines a token containing a name and a category
class Token
{
public:
	enum Type
	{
		BEGIN, END, NEWLINE, // signals to the parser
		LABEL, LOCAL_LABEL, REGISTER, IMMEDIATE, IDENTIFIER, // types of tokens
		ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR // opcodes
	};

	Token() = default;
	Token(char* name, Type type);

	const char* getName();
	Type getType();
	const char* getTypeName();

private:
	char* name;
	Type type;
};

#endif // LEXEME_H
