
#ifndef INCLUDED_VECTOR_H
#define INCLUDED_VECTOR_H

#include "ArrayClass.h"
#include "AbstractVector.h"

class VectorException : public ArrayException {};

template<class DataType>
class Vector : virtual public ArrayClass<DataType>, virtual public AbstractVector<DataType>
{
protected:
	int _currSize;
	int _incFactor;

public:
	Vector();
	Vector(int n);
	Vector(int n, const DataType& val);
	Vector(const Vector<DataType>& v);
	Vector(const ArrayClass<DataType>& ac);
	virtual ~Vector();
	void operator= (const Vector<DataType>& v);
	void operator= (const ArrayClass<DataType>& ac);
	virtual void insert(const DataType& item, int index);
	virtual void remove(int index);
	virtual void add(const DataType& item);
	virtual int size() const;
	virtual int capacity() const;
	virtual int incFactor() const;
	virtual void setIncFactor(int f);
	void setCapacity(int c);
	void clear();
};



template<class DataType>
Vector<DataType>::Vector() : ArrayClass<DataType>()
{
	_currSize = 0;
	_incFactor = 5;
}

template<class DataType>
Vector<DataType>::Vector(int n) : ArrayClass<DataType>(n)
{
	_currSize = 0;
	_incFactor = (n + 1) / 2;
}

template<class DataType>
Vector<DataType>::Vector(int n, const DataType& val) : ArrayClass<DataType>(n, val)
{
	_currSize = 0;
	_incFactor = n/2;
}

template<class DataType>
Vector<DataType>::~Vector() 
{
	
}

template<class DataType>
Vector<DataType>::Vector(const Vector<DataType>& v) : ArrayClass<DataType>(v)
{
	_currSize = v._currSize;
	_incFactor = v._incFactor;
}

template<class DataType>
Vector<DataType>::Vector(const ArrayClass<DataType>& ac) : ArrayClass<DataType>(ac)
{
	_currSize = ac.size();
	_incFactor = (_currSize + 1) / 2;
}

template<class DataType>
void Vector<DataType>::operator= (const Vector<DataType>& v)
{
	ArrayClass<DataType>::copy(v);
	_currSize = v._currSize;
	_incFactor = v._incFactor;
}

template<class DataType>
void Vector<DataType>::operator= (const ArrayClass<DataType>& ac)
{
	ArrayClass<DataType>::copy(ac);
	_currSize = ac.size();
	_incFactor = (_currSize + 1) / 2;
}

template<class DataType>
int Vector<DataType>::size() const
{
	return _currSize;
}

template<class DataType>
int Vector<DataType>::capacity() const
{
	return this->_size; //from ArrayClass.h
}

template<class DataType>
int Vector<DataType>::incFactor() const
{
	return _incFactor;
}

/*Ignore negative values.
*/
template<class DataType>
void Vector<DataType>::setIncFactor(int f)
{
	if (f >= 0) _incFactor = f;
}

template<class DataType>
void Vector<DataType>::setCapacity(int c)
{
	int len = _currSize;
	if (len > c) len = c;
	DataType* paNew = new DataType[c];
	if (!paNew)
	{
		throw ArrayMemoryException();
	}
	for (int i = 0; i < len; ++i)
	{
		paNew[i] = this->pointer_Object[i];
	}
	if (this->pointer_Object)
	{
		delete[] this->pointer_Object;
	}
	this->pointer_Object = paNew;
	this->_size = c;
	if (_currSize > len)
	{
		_currSize = len;
	}

}

template<class DataType>
void Vector<DataType>::insert(const DataType& item, int index)
{
	if ((index < 0) || (index > _currSize))
	{
		throw ArrayBoundsException();
	}
	if (_currSize + 1 == this->_size)
	{
		setCapacity(this->_size + _incFactor);
	}
	_currSize++;

	for (int i = _currSize - 1; i > index; i--)
	{
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[index] = item;
}

template<class DataType>
void Vector<DataType>::add(const DataType& item)
{
	insert(item, _currSize);
}

template<class DataType>
void Vector<DataType>::remove(int index)
{
	if ((index < 0) || (index >= _currSize))
	{
		throw ArrayBoundsException();
	}
	if (_currSize <= this->_size - _incFactor)
	{
		setCapacity(this->_size - _incFactor);
	}
	for (int i = index; i < _currSize - 1; i++)
	{
		(*this)[i] = (*this)[i + 1];
	}
	_currSize--;
}



template<class DataType>
void Vector<DataType>::clear()
{
	for (int i = _currSize - 1; i >= 0; --i)
	{
		remove(i);
	}

}

#endif
