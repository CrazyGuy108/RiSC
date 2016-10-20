#include <fstream>        // for ifstream
#include <iostream>       // for cout
#include "../inc/lexer.h" // for lexer

#define READ_TEST
#define LEXER_TEST

int main()
{
	std::ifstream ifile{ "test.asm" };
	if (ifile.is_open())
	{
		std::cout << "input file opened\n";

		// get file length
		ifile.seekg(0, ifile.end);
		size_t length{ (size_t)ifile.tellg() };
		ifile.seekg(0, ifile.beg);

		// put into char array
		char* contents{ new char[length] };
		ifile.read(contents, length - 1);
		contents[length - 1] = '\0'; // null character to prevent reading garbage data
		
#ifdef READ_TEST
		std::cout << "Read:\n" << contents << '\n';
#endif // READ_TEST
		
#ifdef LEXER_TEST
		std::vector<Lexeme> lexemes{ lexer(contents) };
		std::cout << "Lexer:\n";
		for(Lexeme& lexeme : lexemes)
			std::cout << (lexeme.getName() != nullptr ? lexeme.getName() : "NULL") << ": " << lexeme.getCategory() << '\n';
		std::cout << '\n';
#endif // LEXER_TEST
	}
	else
		std::cout << "error: input file failed to open\n";

	return 0;
}