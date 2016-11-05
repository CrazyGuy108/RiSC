#include "../inc/parsenode.hpp"

ParseNode::~ParseNode()
{

}

Terminal::Terminal(const Token& token)
	: token{ token } {}

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

NonTerminal::~NonTerminal()
{

}
