#ifndef PARSENODE_HPP
#define PARSENODE_HPP

#include "token.hpp" // for Token

// base class for terminal and nonterminal symbols
class ParseNode
{
public:
	virtual ~ParseNode();
};

class Terminal
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

class NonTerminal
	: public ParseNode
{
private:
	NonTerminal() = default;
	virtual ~NonTerminal() override final;

private:
	ParseNode* children;
};

#endif // PARSENODE_HPP
