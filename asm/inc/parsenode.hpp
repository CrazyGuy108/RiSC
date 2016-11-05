#ifndef PARSENODE_HPP
#define PARSENODE_HPP

#include "token.hpp" // for Token

// base class for terminal and nonterminal symbols
class ParseNode
{
public:
	enum Symbol
	{
		PROGRAM,  // program  : BEGIN content ;
		CONTENT,  // content  : label line NEWLINE content | EPSILON ;
		LABEL,    // label    : LABEL | EPSILON ;
		LINE,     // line     : OPCODE operands | EPSILON ;
		OPERANDS, // operands : REG ri1 | IMM | EPSILON ;
		RI1,      // ri1      : REG ri2 | IMM ;
		RI2       // ri2      : REG | IMM ;
	};

	virtual ~ParseNode() = 0;
};

class Terminal final
	: public ParseNode
{
public:
	Terminal() = default;
	Terminal(const Token& token);
	virtual ~Terminal() override final;

	const Token& getToken() const;
	void setToken(const Token& t);

private:
	Token token;
};

class NonTerminal final
	: public ParseNode
{
public:
	NonTerminal() = default;
	virtual ~NonTerminal() override final;

private:
	ParseNode* children;
};

#endif // PARSENODE_HPP
