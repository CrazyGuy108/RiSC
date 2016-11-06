#include "../inc/parsenode.hpp"

ParseNode::ParseNode(Symbol type, ParseNode* parent)
	: type{ type }, parent{ parent } {}

ParseNode::~ParseNode()
{

}

ParseNode::Symbol ParseNode::getType() const
{
	return type;
}

ParseNode* ParseNode::getParent() const
{
	return parent;
}

void ParseNode::setType(Symbol s)
{
	type = s;
}

Terminal::Terminal(Symbol type, ParseNode* parent)
	: ParseNode{ type, parent } {}

Terminal::Terminal(Symbol type, ParseNode* parent, const Token& token)
	: ParseNode{ type, parent }, token{ token } {}

Terminal::~Terminal()
{

}

const Token& Terminal::getToken() const
{
	return token;
}

void Terminal::setToken(const Token& t)
{
	token = t;
}

bool Terminal::isTerminal() const
{
	return true;
}

bool Terminal::isNonTerminal() const
{
	return false;
}

NonTerminal::NonTerminal(Symbol type, ParseNode* parent)
	: ParseNode{ type, parent } {}

NonTerminal::~NonTerminal()
{
	for(ParseNode* node : children)
		if(node != nullptr)
			delete node;
}

void NonTerminal::expand(const production_t& p)
{
	children.clear();
	for (ParseNode::Symbol s : p)
	{
		if (s >= BEGIN && s <= ERROR) // Terminal
			children.push_back(new Terminal{ s, this });
		else if (s >= program && s <= ri1) // NonTerminal
			children.push_back(new NonTerminal{ s, this });
		else
			; // error!
	}
}

const std::vector<ParseNode*>& NonTerminal::getChildren() const
{
	return children;
}

bool NonTerminal::isTerminal() const
{
	return false;
}

bool NonTerminal::isNonTerminal() const
{
	return true;
}
