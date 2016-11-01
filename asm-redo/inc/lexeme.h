#ifndef LEXEME_H
#define LEXEME_H

#include <iostream> // for ostream

// non-terminated substring of the source code
class Lexeme
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Lexeme& l);
	friend bool operator<(const Lexeme& l, const Lexeme& r);

	Lexeme() = default;
	Lexeme(const char* beg, const char* end);

	template<size_t len>
	Lexeme(const char str[len])
		: Lexeme{ str, &str[len] } {}

	const char* getBeg() const; // gets beg
	const char* getEnd() const; // gets end

	void setBeg(const char* beg); // sets beg
	void setEnd(const char* end); // sets end

	size_t length() const; // gets length of substring

	int cmp(const Lexeme& l) const;

private:
	const char* beg; // beginning of lexeme
	const char* end; // end of lexeme
};

#endif // LEXEME_H
