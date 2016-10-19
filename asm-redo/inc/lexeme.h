#ifndef LEXEME_H
#define LEXEME_H

// defines a lexeme containing a token name and a token category
class Lexeme
{
public:
	enum Category
	{
		IDENTIFIER, LABEL, LOCAL_LABEL, REGISTER, IMMEDIATE, NEWLINE,
		ADD, ADDI, NAND, LUI, SW, LW, BEQ, JALR
	};

	Lexeme(char* name, Category category);

private:
	char* name;
	Category category;
};

#endif // LEXEME_H