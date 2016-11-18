#include <fstream>              // for ifstream
#include <iostream>             // for cout
#include <string>               // for string
#include "../inc/lexer.hpp"     // for Lexer
#include "../inc/parser.hpp"    // for Parser
#include "../inc/generator.hpp" // for Generator

#define READ_TEST
//#define LEXER_TEST
//#define PARSER_TEST
#define GEN_TEST

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

		// print out every Token created by the lexer
		while (!lexer.empty())
			std::cout << lexer.next() << '\n';

		std::cout << "errors found: " << lexer.getErrors() << '\n' << std::endl;
#endif // LEXER_TEST

#ifdef PARSER_TEST
		std::cout << "Parser:" << std::endl;
		Parser parser{ Lexer{ contents.c_str() } };

		// print out every Line created by the parser
		while(!parser.empty())
			std::cout << *parser.next() << '\n';

		std::cout << "errors found: " << parser.getErrors() << '\n' << std::endl;
#endif // PARSER_TEST

#ifdef GEN_TEST
		std::cout << "Generator:" << std::endl;
		Generator generator{ Parser{ Lexer{ contents.c_str() } } };

		// print out every line of bytecode
		while(!generator.empty())
			std::cout << std::hex << generator.next() << '\n';

		std::cout << "\nSymbol table:\n";

		// print out symbol table
		for (const auto& i : generator.getSymbolTable())
			std::cout << i.first << ": " << i.second << '\n';

		std::cout << "errors found: " << generator.getErrors() << '\n' << std::endl;
#endif // GEN_TEST

		ifile.close();
		std::cout << "input file closed\n";
	}
	else
		std::cout << "error: input file failed to open\n";

	std::cout << std::endl;

	return 0;
}
