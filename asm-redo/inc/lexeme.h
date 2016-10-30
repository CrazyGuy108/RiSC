#ifndef LEXEME_H
#define LEXEME_H

// non-terminated substring of the source code
class Lexeme
{
	Lexeme(const char* beg, const char* end);

	const char* getBeg(); // gets beg
	const char* getEnd(); // gets end

private:
	const char* beg; // beginning of lexeme
	const char* end; // end of lexeme
};

#endif // LEXEME_H
