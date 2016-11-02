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
		std::cout << "Lexer:" << std::endl;
		Lexer lexer{ contents.c_str() };

		while (!lexer.empty())
			std::cout << lexer.next() << '\n';

		std::cout << std::endl;
#endif // LEXER_TEST

		ifile.close();
		std::cout << "input file closed\n";
	}
	else
		std::cout << "error: input file failed to open\n";

	std::cout << std::endl;

	return 0;
}
