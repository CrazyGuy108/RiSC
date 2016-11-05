#ifndef PARSENODE_HPP
#define PARSENODE_HPP

#include "token.hpp" // for Token

// base class for terminal and nonterminal symbols
class ParseNode
{
public:
	enum Symbol
	{
		// NonTerminals
		program,  // program  : BEGIN content ;
		content,  // content  : label line NEWLINE content | EPSILON ;
		label,    // label    : LABEL | EPSILON ;
		line,     // line     : OPCODE operands | EPSILON ;
		operands, // operands : REG ri1 | IMM | EPSILON ;
		ri1,      // ri1      : REG ri2 | IMM ;
		ri2,      // ri2      : REG | IMM ;

		// Terminals
		BEGIN,
		LABEL,
		OPCODE,
		REG,
		IMM,
		NEWLINE,
		EPSILON,
		ERROR
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
