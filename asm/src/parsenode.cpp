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

const std::vector<ParseNode*>&& ParseNode::getSiblings() const
{
	return std::forward<const std::vector<ParseNode*>>(parent->getChildren());
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

const std::vector<ParseNode*>&& Terminal::getChildren() const
{
	return std::forward<const std::vector<ParseNode*>>({});
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
	for (production_t::value_type s : p)
	{
		if (s >= BEGIN && s <= ERROR) // Terminal
			children.push_back(new Terminal{ s, this });
		else if (s >= program && s <= ri1) // NonTerminal
			children.push_back(new NonTerminal{ s, this });
		else
			; // error!
	}
}

const std::vector<ParseNode*>&& NonTerminal::getChildren() const
{
	return std::forward<const std::vector<ParseNode*>>(children);
}
