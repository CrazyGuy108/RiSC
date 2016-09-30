#ifndef EXCEPTION_H
#define EXCEPTION_H

// base class for all exceptions
class RiscException
{
public:
	RiscException();
	RiscException(const char* msg);

	virtual const char* what() const; // gets the message

protected:
	const char* msg; // details about the exception
};

// unresolved symbols/tokens exception
class TokenException
	: public RiscException
{
public:
	TokenException();
	TokenException(const char* msg);
};

// symbol already defined exception
class SymbolException
	: public RiscException
{
public:
	SymbolException();
	SymbolException(const char* msg);
};

#endif // EXCEPTION_H