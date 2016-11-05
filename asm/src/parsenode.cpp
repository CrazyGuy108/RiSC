#include "../inc/parsenode.hpp"

Terminal::Terminal(const Token& token)
	: token{ token } {}

const Token& Terminal::getToken() const
{
	return token;
}

void Terminal::setToken(const Token& t)
{
	token = t;
}
