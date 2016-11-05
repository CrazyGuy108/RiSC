#include "../inc/parsetree.hpp"

ParseTree::ParseTree(const char* program)
{
	parse(program);
}

ParseTree::ParseTree(Lexer& lexer)
{
	parse(lexer);
}

void ParseTree::parse(const char* program)
{
	parse(Lexer{ program });
}

void ParseTree::parse(Lexer& lexer)
{
	static const production_t
		error{ { ParseNode::ERROR } },
		epsilon{ { ParseNode::EPSILON } },
		reg{ { ParseNode::REG } },
		imm{ { ParseNode::IMM } },
		program{ ParseNode::BEGIN, ParseNode::content },
		content{ { ParseNode::label, ParseNode::line, ParseNode::NEWLINE, ParseNode::content } },
		label{ { ParseNode::LABEL } },
		line{ { ParseNode::OPCODE, ParseNode::operands } },
		operands{ { ParseNode::REG, ParseNode::ri1 } },
		ri1{ { ParseNode::REG, ParseNode::ri2 } };

	static const production_t* parseTable[7][9]
	{
		// program
		{
			// BEGIN, END, NEWLINE, KEYWORD, LABEL
			&program, &error, &error, &error, &error,
			// REGISTER, IMMEDIATE, IDENTIFIER, ERROR
			&error, &error, &error, &error
		},
		// content
		{
			// BEGIN, END, NEWLINE, KEYWORD, LABEL
			&error, &epsilon, &content, &content, &content,
			// REGISTER, IMMEDIATE, IDENTIFIER, ERROR
			&error, &error, &error, &error
		},
		// label
		{
			// BEGIN, END, NEWLINE, KEYWORD, LABEL
			&error, &error, &epsilon, &epsilon, &label,
			// REGISTER, IMMEDIATE, IDENTIFIER, ERROR
			&error, &error, &error, &error
		},
		// line
		{
			// BEGIN, END, NEWLINE, KEYWORD, LABEL
			&error, &error, &epsilon, &line, &error,
			// REGISTER, IMMEDIATE, IDENTIFIER, ERROR
			&error, &error, &error, &error
		},
		// operands
		{
			// BEGIN, END, NEWLINE, KEYWORD, LABEL
			&error, &error, &epsilon, &error, &error,
			// REGISTER, IMMEDIATE, IDENTIFIER, ERROR
			&operands, &imm, &error, &error
		},
		// ri1
		{
			// BEGIN, END, NEWLINE, KEYWORD, LABEL
			&error, &error, &epsilon, &error, &error,
			// REGISTER, IMMEDIATE, IDENTIFIER, ERROR
			&ri1, &imm, &error, &error
		},
		// ri2
		{
			// BEGIN, END, NEWLINE, KEYWORD, LABEL
			&error, &error, &epsilon, &error, &error,
			// REGISTER, IMMEDIATE, IDENTIFIER, ERROR
			&reg, &imm, &error, &error
		}
	};

	Token token;
	while (!lexer.empty())
	{
		token = lexer.next();
		// match against parse table
	}
}
