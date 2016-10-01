#ifndef EXCEPTION_H
#define EXCEPTION_H

// base class for all exceptions
class RiscException
{
public:
	RiscException();
	RiscException(const char* msg);

	const char* what() const; // gets the message

protected:
	const char* msg; // details about the exception
};

// unresolved token exception
class TokenException
	: public RiscException
{
public:
	TokenException();
	TokenException(const char* token);
};

// redefined symbol exception
class SymbolException
	: public RiscException
{
public:
	SymbolException();
	SymbolException(const char* symbol);
};

// unexpected operand amount exception
class OperandException
	: public RiscException
{
public:
	OperandException();
	OperandException(const char* opcode, size_t expected, size_t given);
	
	size_t getExpected() const; // gets expected operand count
	size_t getGiven() const;    // gets given operand count

protected:
	size_t expected; // amount of operands expected
	size_t given;    // amount of operands given
};

#endif // EXCEPTION_H