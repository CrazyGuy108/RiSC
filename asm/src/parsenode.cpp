#include "../inc/parsenode.hpp"

const Token& Terminal::getToken() const
{
	return token;
}

void Terminal::setToken(const Token& t)
{
	token = t;
}
