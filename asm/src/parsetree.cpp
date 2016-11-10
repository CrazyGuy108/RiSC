#include "../inc/parsetree.hpp"

template<typename T>
ParseTree::base_iterator<T>::base_iterator(pointer ptr)
	: ptr{ ptr }, indexes{} {}

template<typename T>
bool ParseTree::base_iterator<T>::operator==(const base_iterator<T>& a) const
{
	return ptr == a.ptr;
}

template<typename T>
bool ParseTree::base_iterator<T>::operator!=(const base_iterator<T>& a) const
{
	return ptr != a.ptr;
}

template<typename T>
typename ParseTree::base_iterator<T>::reference ParseTree::base_iterator<T>::operator*() const
{
	return *ptr;
}

template<typename T>
typename ParseTree::base_iterator<T>::pointer ParseTree::base_iterator<T>::operator->() const
{
	return ptr;
}

template<typename T>
ParseTree::base_iterator<T> ParseTree::base_iterator<T>::operator++()
{
	// advance pointer
	return *this;
}

template<typename T>
ParseTree::base_iterator<T> ParseTree::base_iterator<T>::operator++(int)
{
	const_iterator tmp{ *this };
	++(*this);
	return tmp;
}

ParseTree::ParseTree(const char* program)
	: root{ new NonTerminal{ ParseNode::program, nullptr } }, node{ root }
{
	parse(program);
}

ParseTree::ParseTree(Lexer& lexer)
	: root{ new NonTerminal{ ParseNode::program, nullptr } }, node{ root }
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

ParseTree::iterator ParseTree::begin() const
{
	return iterator{ root };
}

ParseTree::iterator ParseTree::end() const
{
	return iterator{ nullptr };
}

ParseTree::const_iterator ParseTree::cbegin() const
{
	return const_iterator{ root };
}

ParseTree::const_iterator ParseTree::cend() const
{
	return const_iterator{ nullptr };
}

void ParseTree::advanceNode()
{
	const std::vector<ParseNode*>& children{ node->getChildren() };
	if (children.empty())
	{
		// go to the next sibling
		// but if this is the last sibling, backtrack and try again
	}
	else
	{
		// go to the next child
	}
}
