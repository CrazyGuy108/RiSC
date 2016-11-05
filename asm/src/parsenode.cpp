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

bool ParseNode::isTerminal() const
{
	return type >= BEGIN && type <= ERROR;
}

bool ParseNode::isNonTerminal() const
{
	return type >= program && type <= ri1;
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

NonTerminal::NonTerminal(Symbol type)
	: ParseNode{ type } {}

NonTerminal::~NonTerminal()
{

}
