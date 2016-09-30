#include "../include/exception.h"

RiscException::RiscException()
	: msg{ nullptr } {}

RiscException::RiscException(const char* msg)
	: msg{ msg } {}

const char* RiscException::what() const
{
	return (msg == nullptr) ? "unknown error!" : msg;
}

TokenException::TokenException()
	: RiscException{} {}

TokenException::TokenException(const char* msg)
	: RiscException{ msg } {}

SymbolException::SymbolException()
	: RiscException{} {}

SymbolException::SymbolException(const char* msg)
	: RiscException{ msg } {}

OperandException::OperandException()
	: RiscException{}, expected{ 0 }, given{ 0 } {}

OperandException::OperandException(const char* opcode, size_t expected, size_t given)
	: RiscException{ opcode }, expected{ expected }, given{ given } {}

size_t OperandException::getExpected() const
{
	return expected;
}

size_t OperandException::getGiven() const
{
	return given;
}