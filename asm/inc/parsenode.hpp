#ifndef PARSENODE_HPP
#define PARSENODE_HPP

#include <vector>
#include "token.hpp"   // for Token

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

	ParseNode() = default;
	ParseNode(Symbol type);
	virtual ~ParseNode() = 0;

	Symbol getType() const;
	void setType(Symbol s);

	virtual bool isTerminal() const = 0;
	virtual bool isNonTerminal() const = 0;

protected:
	Symbol type; // tells the parser what kind of node it is
};

typedef std::vector<ParseNode::Symbol> production_t;

class Terminal final
	: public ParseNode
{
public:
	Terminal() = default;
	Terminal(Symbol type);
	Terminal(Symbol type, const Token& token);
	virtual ~Terminal() override final;

	const Token& getToken() const;
	void setToken(const Token& t);

	virtual bool isTerminal() const override final;
	virtual bool isNonTerminal() const override final;

private:
	Token token;
};

class NonTerminal final
	: public ParseNode
{
public:
	NonTerminal() = default;
	NonTerminal(Symbol type);
	virtual ~NonTerminal() override final;

	void expand(const production_t& p);

	virtual bool isTerminal() const override final;
	virtual bool isNonTerminal() const override final;

private:
	std::vector<ParseNode*> children;
};

#endif // PARSENODE_HPP
