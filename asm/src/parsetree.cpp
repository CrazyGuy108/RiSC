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
			&program, // BEGIN
			&error,   // END
			&error,   // NEWLINE
			&error,   // KEYWORD
			&error,   // LABEL
			&error,   // REGISTER
			&error,   // IMMEDIATE
			&error,   // IDENTIFIER
			&error    // ERROR
		},
		// content
		{
			&error,   // BEGIN
			&epsilon, // END
			&content, // NEWLINE
			&content, // KEYWORD
			&content, // LABEL
			&error,   // REGISTER
			&error,   // IMMEDIATE
			&error,   // IDENTIFIER
			&error    // ERROR
		},
		// label
		{
			&error,   // BEGIN
			&error,   // END
			&epsilon, // NEWLINE
			&epsilon, // KEYWORD
			&label,   // LABEL
			&error,   // REGISTER
			&error,   // IMMEDIATE
			&error,   // IDENTIFIER
			&error    // ERROR
		},
		// line
		{
			&error,   // BEGIN
			&error,   // END
			&epsilon, // NEWLINE
			&line,    // KEYWORD
			&error,   // LABEL
			&error,   // REGISTER
			&error,   // IMMEDIATE
			&error,   // IDENTIFIER
			&error    // ERROR
		},
		// operands
		{
			&error,    // BEGIN
			&error,    // END
			&epsilon,  // NEWLINE
			&error,    // KEYWORD
			&error,    // LABEL
			&operands, // REGISTER
			&imm,      // IMMEDIATE
			&error,    // IDENTIFIER
			&error     // ERROR
		},
		// ri1
		{
			&error,   // BEGIN
			&error,   // END
			&epsilon, // NEWLINE
			&error,   // KEYWORD
			&error,   // LABEL
			&ri1,     // REGISTER
			&imm,     // IMMEDIATE
			&error,   // IDENTIFIER
			&error    // ERROR
		},
		// ri2
		{
			&error,   // BEGIN
			&error,   // END
			&epsilon, // NEWLINE
			&error,   // KEYWORD
			&error,   // LABEL
			&reg,     // REGISTER
			&imm,     // IMMEDIATE
			&error,   // IDENTIFIER
			&error    // ERROR
		}
	};

	Token token;
	while (!lexer.empty())
	{
		token = lexer.next();
		// match against parse table
	}
}
