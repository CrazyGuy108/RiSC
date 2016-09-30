#include "../include/exception.h"

RiscException::RiscException()
	: msg{ nullptr } {}

RiscException::RiscException(const char* msg)
	: msg{ msg } {}

const char* RiscException::what() const
{
	return msg;
}

TokenException::TokenException()
	: RiscException{} {}

TokenException::TokenException(const char* msg)
	: RiscException{ msg } {}