#ifndef LEXEME_H
#define LEXEME_H

// defines a lexeme containing a token name and a token category
class Lexeme
{
public:
	enum Category
	{
		BEGIN, END, NEWLINE, // signals to the parser
		LABEL, LOCAL_LABEL, REGISTER, IMMEDIATE, IDENTIFIER, // types of tokens
		ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR // opcodes
	};

	Lexeme() = default;
	Lexeme(char* name, Category category);

	const char* getName();
	Category getCategory();
	const char* getCategoryName();

private:
	char* name;
	Category category;
};

#endif // LEXEME_H
