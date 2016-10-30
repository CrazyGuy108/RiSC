#include <fstream>        // for ifstream
#include <iostream>       // for cout
#include <string>         // for string
#include "../inc/lexer.h" // for lexer

#define READ_TEST
#define LEXER_TEST

int main()
{
	std::ifstream ifile{ "test.asm" };
	if (ifile.is_open())
	{
		std::string contents{ std::istreambuf_iterator<char>{ ifile }, std::istreambuf_iterator<char>{} };
		std::cout << "input file opened\n";

#ifdef READ_TEST
		std::cout << "Read:\n" << contents << '\n';
#endif // READ_TEST
		
#ifdef LEXER_TEST
		std::cout << "Lexer:\n";
		Lexer lexer{ contents.c_str() };
		Token lexeme;

		while (lexeme.getType() != Token::END)
		{
			lexeme = lexer.next();
			std::cout << lexeme.getName() << ": " << lexeme.getTypeName() << '\n';
		}

		std::cout << '\n';
#endif // LEXER_TEST
	}
	else
		std::cout << "error: input file failed to open\n";

	return 0;
}