#ifndef LEXEME_H
#define LEXEME_H

// defines a lexeme containing a token name and a token category
class Lexeme
{
public:
	enum Category
	{
		UNDEFINED, LABEL, LOCAL_LABEL, OPCODE, REGISTER
	};

	Lexeme(char* name, Category category = UNDEFINED);

private:
	char* name;
	Category category;
};

#endif // LEXEME_H
