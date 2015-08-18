#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H


#include <cstring>
#include "ArrayClass.h"
#include "Exception.h"
#include "Vector.h"


#pragma GCC diagnostic ignored "-Wwrite-strings"

class BStringSizeException : public ArrayException { };

class BString : virtual public ArrayClass<char>
{

public:
	BString();
	BString(int n);
	BString(char* s);
	~BString();
	BString(const BString& str);
	virtual int size() const;
	virtual int length() const;
	void operator= (const BString& str);
	bool operator== (const BString& str) const;
	bool operator< (const BString& str) const;
	void concatenate(const BString& str);
	int index(char c, int start) const;
	int index(char c) const;
	BString substring(int left, int len) const;
	BString operator+ (const BString& str);
	bool equalsIgnoreCase(const BString& str);
	BString convertFromVector(Vector<char>& vec);
	bool operator!= (const BString& str) const;
	friend ostream& operator << (ostream& s, const BString& str)
	{
		s << str.pointer_Object;
		return s;
	}
};

BString::BString() : ArrayClass<char>(1,'\0') {}

BString::BString(int n) : ArrayClass<char>(n+1,'\0') {}

BString::BString(char* s) : ArrayClass<char>(strlen(s)+1)
{
	std::strcpy(pointer_Object, s);
}

BString::~BString() {}

//copy constructor
BString::BString(const BString& str) : ArrayClass<char> (str) { }

//This returns absolute size minus null terminated bit
int BString::size() const
{
	return ArrayClass<char>::size()-1;
}

//returns current length before nul terminated bit.
int BString::length() const
{
	return strlen(pointer_Object);
}

void BString::operator= (const BString& str)
{
	if(size() == 0) 
	{
		//call parent 
		ArrayClass<char>::operator= (str);
		return;
	}
	int max = str.length();//all chars before null terminate
	bool overflow = false;
	if (size() < max)   //if size() is less than length() we overflow
	{
		overflow = true;
		max = size();//will truncate if exception is caught
	}

	strncpy (pointer_Object, str.pointer_Object, max);
	pointer_Object[max] = '\0'; //always null terminate!
	if(overflow) throw BStringSizeException();
}

bool BString::operator== (const BString& str) const
{
	return (strcmp(pointer_Object, str.pointer_Object) == 0);
}

bool BString::operator< (const BString& str) const
{
	return (strcmp(pointer_Object, str.pointer_Object) < 0);
}

void BString::concatenate(const BString& str)
{
	int len = length();
	int max = str.length();
	bool overflow = false;
	if (size() < max + len)
	{
		overflow = true;
		max = size() - len;
	}
	strncpy(pointer_Object + len, str.pointer_Object, max);
	pointer_Object[max + len] = '\0'; //always null terminate!
	if (overflow) throw BStringSizeException();

}

int BString::index(char c, int start) const
{
	if (start >= length()) return -1;
	char* pc = strchr(pointer_Object + start, c);
	if (pc == NULL) return -1;
	return (pc - pointer_Object);
}

int BString::index(char c) const
{
	return index(c, 0);
}

BString BString::substring(int left, int len) const
{
	if (left < 0) throw ArrayBoundsException();

	BString sub(len);
	if (left > length()) return sub;
	int max = len;
	if (max + left > length()) max = length() - left;
	strncpy(sub.pointer_Object, &pointer_Object[left], max);
	sub.pointer_Object[max] = '\0'; //always null terminate!!
	return sub;
}

BString BString::operator+ (const BString& str)
{
	BString temp(length() + str.length());
	temp = (*this);
	temp.concatenate(str);
	return temp;
}

bool BString::equalsIgnoreCase(const BString& str)
{
	return (strcasecmp(pointer_Object, str.pointer_Object));
}

BString BString::convertFromVector(Vector<char>& vec)
{
	BString myString(vec.size() + 1);
	for (int i = 0; i < vec.size(); ++i)
	{
		myString.pointer_Object[i] = vec[i];
	}
	myString.pointer_Object[vec.size() + 1] = '\0'; //always null terminate.

	return myString;
}

bool BString::operator!= (const BString& str) const
{
	return !((strcmp(pointer_Object, str.pointer_Object) < 0));
}
#endif
