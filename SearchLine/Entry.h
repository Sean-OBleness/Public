#ifndef a252430c_3897_11e5_9ee2_0862664ad4ff_ENTRY_H
#define a252430c_3897_11e5_9ee2_0862664ad4ff_ENTRY_H

#include "BetterString.h"

class Entry
{
private:
	BString _content;
	int _line;

public:
	Entry(int line, BString& content);
	~Entry();
	Entry(const Entry& e)
	int line();
	BString& content();
};

Entry::Entry(int line, BString& content) : _content(100)
{
	_line = line;
	_content = content;
}

Entry::~Entry() { }

Entry::Entry(const Entry& e) : _content(100)
{
	_line = e._line;
	_content = e._content;
}

int Entry::line()
{
	return _line;
}

BString& Entry::content()
{
	return _content;
}

#endif
