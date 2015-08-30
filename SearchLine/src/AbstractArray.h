#ifndef _ABSTRACTARRAY_H
#define _ABSTRACTARRAY_H

#include <iostream>
#include "Exception.h"

using namespace std;

class ArrayException : public Exception {};
class ArrayMemoryException : public ArrayException {};
class ArrayBoundsException : public ArrayException {};
class ArrayDataNotFound : public ArrayException {};

template <class DataType>
class AbstractArrayClass
{

	public:
		virtual int size() const = 0;
		virtual DataType& operator[] (int k) const = 0;
		friend ostream& operator << (ostream& s, AbstractArrayClass<DataType>& ac)
		{
        		s << '[';
        		for (int i = 0; i < ac.size(); ++i)
        		{
                		if (i > 0)
                		{
                        		s << ',';
                		}
                		s << ac[i];
        		}
        		s << ']';
        		return s;

		};

};

#endif
