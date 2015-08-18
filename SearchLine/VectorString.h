#ifndef INCLUDED_VECTOR_STRING_H
#define INCLUDED_VECTOR_STRING_H


#include <cstring>
#include "Vector.h"
#include "Exception.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

class VectorStringException : public VectorException { };

class VString : virtual public Vector<char>
{

public:
	VString();
	VString(int n);
	VString(char* s);
	~VString();
	VString(const VString& str);
	virtual int size() const;
	virtual int length() const;
	void operator= (const VString& str);
	friend ostream& operator << (ostream& s, const VString& str)
	{
		s << str.pointer_Object;
		return s;
	}
};

VString::VString() : Vector<char>(1,'\0') {}

VString::VString(int n) : Vector<char>(n+1,'\0') {}

VString::VString(char* s) : Vector<char>(strlen(s)+1)
{
	std::strcpy(pointer_Object, s);
}

VString::~VString() {}

VString::VString(const VString& str) : Vector<char> (str) { }

//This returns absolute size minus null terminated bit
int VString::size() const
{
	return Vector<char>::size()-1;
}

//returns current length before nul terminated bit.
int VString::length() const
{
	return strlen(pointer_Object);
}

void VString::operator= (const VString& str)
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
	if(overflow) throw VectorStringException();
}


#endif
