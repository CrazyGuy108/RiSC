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

#endif // EXCEPTION_H