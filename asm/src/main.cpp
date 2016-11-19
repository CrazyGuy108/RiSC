#include <fstream>              // for ifstream
#include <iostream>             // for cout
#include <string>               // for string
#include "../inc/lexer.hpp"     // for Lexer
#include "../inc/parser.hpp"    // for Parser
#include "../inc/generator.hpp" // for Generator

//#define READ_TEST
//#define LEXER_TEST
//#define PARSER_TEST
//#define GEN_TEST

#if defined(READ_TEST) || defined(LEXER_TEST) || defined(PARSER_TEST) || defined(GEN_TEST)
#define IF_TEST(...) __VA_ARGS__
#else
#define IF_TEST(...)
#endif

#ifdef READ_TEST
#define IF_READ(...) __VA_ARGS__
#else
#define IF_READ(...)
#endif

#ifdef LEXER_TEST
#define IF_LEXER(...) __VA_ARGS__
#else
#define IF_LEXER(...)
#endif

#ifdef PARSER_TEST
#define IF_PARSER(...) __VA_ARGS__
#else
#define IF_PARSER(...)
#endif

#ifdef GEN_TEST
#define IF_GEN(...) __VA_ARGS__
#else
#define IF_GEN(...)
#endif

int main(int argc, char** argv)
{
	IF_TEST
	(
		argc = 3;
		argv = new char*[3];
		argv[1] = "test.asm";
		argv[2] = "test.risc";
	)
	if(argc == 3)
	{
		const char* ext{ strrchr(argv[1], '.') };
		if (ext && !strcmp(ext, ".asm"))
		{
			std::ifstream ifile{ argv[1] };
			if (ifile.is_open())
			{
				std::string contents{ std::istreambuf_iterator<char>{ ifile }, std::istreambuf_iterator<char>{} };
				IF_TEST(std::cout << "input file opened\n");
				IF_READ(std::cout << "Read:\n" << contents << '\n');
				IF_LEXER
				(
					std::cout << "Lexer:" << std::endl;
					Lexer lexer{ contents.c_str() };

					// print out every Token created by the lexer
					while (!lexer.empty())
						std::cout << lexer.next() << '\n';

					std::cout << "errors found: " << lexer.getErrors() << '\n' << std::endl;
				)
				IF_PARSER
				(
					std::cout << "Parser:" << std::endl;
					Parser parser{ Lexer{ contents.c_str() } };

					// print out every Line created by the parser
					while (!parser.empty())
						std::cout << *parser.next() << '\n';

					std::cout << "errors found: " << parser.getErrors() << '\n' << std::endl;
				)
				IF_GEN
				(
					std::cout << "Generator:" << std::endl;
					Generator generator{ Parser{ Lexer{ contents.c_str() } } };

					// print out every line of bytecode
					while (!generator.empty())
						std::cout << std::hex << generator.next() << '\n';

					std::cout << "\nSymbol table:\n";

					// print out symbol table
					for (const auto& i : generator.getSymbolTable())
						std::cout << i.first << ": " << i.second << '\n';

					std::cout << "errors found: " << generator.getErrors() << '\n' << std::endl;
				)
				// go through the entire compilation process
				Lexer l{ contents.c_str() };
				Parser p{ l };
				Generator g{ p };

				ifile.close();
				IF_TEST(std::cout << "input file closed\n");

				if (!l.getErrors() && !p.getErrors() && !g.getErrors())
				{
					ext = strrchr(argv[2], '.');
					if (ext && !strcmp(ext, ".risc"))
					{
						std::ofstream ofile{ argv[2], std::ofstream::binary };
						if (ofile.is_open())
						{
							IF_TEST(std::cout << "output file opened\n");

							while (!g.empty())
							{
								inst_t inst{ g.next() };
								char bytes[2]{ (inst & 0xff00) >> 8, inst & 0x00ff };
								ofile.write(bytes, 2);
							}

							ofile.close();
							IF_TEST(std::cout << "output file closed\n");
						}
						else
							std::cout << "error: output file failed to open\n";
					}
					else
						std::cout << "error: invalid file extension for output file\n";
				}
				else
					std::cout << "errors found: " << (l.getErrors() + p.getErrors() + g.getErrors()) << '\n';
			}
			else
				std::cout << "error: input file failed to open\n";
		}
		else
			std::cout << "error: invalid file extension for input file\n";
	}
	else
		std::cout << "error: requires 2 arguments: src and dest\n";
	IF_TEST(delete[] argv);

	return 0;
}
