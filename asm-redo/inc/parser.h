#ifndef PARSER_H
#define PARSER_H

class Parser
{
public:
	Parser() = default;
	Parser(char* program); // lex and parse program

	void parse(char* program);
};

#endif // PARSER_H
