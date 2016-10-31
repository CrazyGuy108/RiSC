#ifndef LEXEME_H
#define LEXEME_H

#include <iostream> // for ostream

// non-terminated substring of the source code
class Lexeme
{
public:
	friend std::ostream& operator<<(std::ostream& os, Lexeme& l);

	Lexeme(const char* beg, const char* end);

	const char* getBeg(); // gets beg
	const char* getEnd(); // gets end

	size_t length(); // gets length of substring

private:
	const char* beg; // beginning of lexeme
	const char* end; // end of lexeme
};

#endif // LEXEME_H
