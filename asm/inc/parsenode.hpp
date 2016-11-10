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
	ParseNode(Symbol type, ParseNode* parent);
	virtual ~ParseNode() = 0;

	Symbol getType() const;
	ParseNode* getParent() const;
	const std::vector<ParseNode*>&& getSiblings() const;
	virtual const std::vector<ParseNode*>&& getChildren() const = 0;

	void setType(Symbol s);

protected:
	Symbol type;                      // tells the parser what kind of node it is
	ParseNode* parent;                // pointer to the parent node
};

typedef std::vector<ParseNode::Symbol> production_t;

class Terminal final
	: public ParseNode
{
public:
	Terminal() = default;
	Terminal(Symbol type, ParseNode* parent);
	Terminal(Symbol type, ParseNode* parent, const Token& token);
	virtual ~Terminal() override final;

	const Token& getToken() const;
	void setToken(const Token& t);

	virtual const std::vector<ParseNode*>&& getChildren() const override final;

private:
	Token token;
};

class NonTerminal final
	: public ParseNode
{
public:
	NonTerminal() = default;
	NonTerminal(Symbol type, ParseNode* parent);
	virtual ~NonTerminal() override final;

	void expand(const production_t& p);

	virtual const std::vector<ParseNode*>&& getChildren() const override final;

private:
	std::vector<ParseNode*> children; // children of this node
};

#endif // PARSENODE_HPP
