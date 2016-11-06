#include "../inc/parsenode.hpp"

ParseNode::ParseNode(Symbol type)
	: type{ type } {}

ParseNode::~ParseNode()
{

}

ParseNode::Symbol ParseNode::getType() const
{
	return type;
}

void ParseNode::setType(Symbol s)
{
	type = s;
}

Terminal::Terminal(Symbol type)
	: ParseNode{ type } {}

Terminal::Terminal(Symbol type, const Token& token)
	: ParseNode{ type }, token{ token } {}

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

NonTerminal::NonTerminal(Symbol type)
	: ParseNode{ type } {}

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
			children.push_back(new Terminal{ s });
		else if (s >= program && s <= ri1) // NonTerminal
			children.push_back(new NonTerminal{ s });
		else
			; // error!
	}
}

bool NonTerminal::isTerminal() const
{
	return false;
}

bool NonTerminal::isNonTerminal() const
{
	return true;
}
