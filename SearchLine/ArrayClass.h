#ifndef INCLUDED_ARRAYCLASS_H
#define INCLUDED_ARRAYCLASS_H

#include <iostream>
#include "AbstractArray.h"

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

template <class DataType>
class ArrayClass : virtual public AbstractArrayClass<DataType>
{
	protected:
		DataType* pointer_Object;
		int _size;
		void copy(const ArrayClass<DataType>& ac);
		void _quicksort(int left, int right);
		int _binarysearch(const DataType& data, int left, int right);
	public:
		ArrayClass();
		ArrayClass(int i);
		~ArrayClass();
		ArrayClass(const ArrayClass<DataType>& ac);
		ArrayClass(int i, const DataType& value);
		virtual int size() const;
	        virtual DataType& operator[] (int k) const;
	        void operator= (const ArrayClass<DataType>& ac);
		void quicksort();
		int binarysearch(const DataType& data);
};

template <class DataType>
ArrayClass<DataType>::ArrayClass()
{
	_size = 0;
	pointer_Object = new DataType[ARRAY_CLASS_DEFAULT_SIZE];
	if (!pointer_Object) throw ArrayMemoryException();
	_size = ARRAY_CLASS_DEFAULT_SIZE;
}

template <class DataType>
ArrayClass<DataType>::ArrayClass(int i)
{
	_size = 0;
	pointer_Object = new DataType[i];
	if (!pointer_Object) throw ArrayMemoryException();
	_size = i;
}

template <class DataType>
ArrayClass<DataType>::~ArrayClass()
{
	if(pointer_Object) delete[] pointer_Object;
	pointer_Object = 0;
	_size = 0;
}

template <class DataType>
ArrayClass<DataType>::ArrayClass(const ArrayClass<DataType>& ac)
{
        if (&ac != this) //don't allow an object to copy itself
        {
                copy(ac);
        }
}

template <class DataType>
ArrayClass<DataType>::ArrayClass(int i, const DataType& value)
{
        _size = 0;
        pointer_Object = new DataType[i];
        if (!pointer_Object) throw ArrayMemoryException();
        _size = i;
        for (int j = 0; j < i; ++j)
        {
                pointer_Object[j] = value;
        }
}

template <class DataType>
void ArrayClass<DataType>::copy(const ArrayClass<DataType>& ac)
{
        _size = 0;
        pointer_Object = new DataType[ac._size];
        if (!pointer_Object) throw ArrayMemoryException();
        _size = ac._size;
        for (int i = 0; i < _size; ++i)
        {
                pointer_Object[i] = ac.pointer_Object[i];
        }
}

template <class DataType>
int ArrayClass<DataType>::size() const
{
        return _size;
}

template <class DataType>
DataType& ArrayClass<DataType>::operator[](int k) const
{
        if ((k < 0) || (k >= size())) throw ArrayBoundsException();
        return pointer_Object[k];
}

template <class DataType>
void ArrayClass<DataType>::operator= (const ArrayClass<DataType>& ac)
{
        if (&ac != this)
        {
                if (pointer_Object) delete[] pointer_Object;
                copy(ac);
        }
}

template <class DataType>
void ArrayClass<DataType>::_quicksort(int left, int right)
{

        if (left < right)
        {
                DataType& pivot = pointer_Object[left];

                int i = left;
                int j = right+1;
                do{
                        do{
                                i++;
                        } while ((i < _size) && (pointer_Object[i] < pivot));
                        do{
                                j--;
                        } while (pointer_Object[j] > pivot);
                        if (i < j)
                                swap(pointer_Object[i], pointer_Object[j]);
                } while (i < j);
                swap(pointer_Object[left], pointer_Object[j]);

                _quicksort(left, j - 1);
                _quicksort(j + 1, right);

        }
}

template <class DataType>
void ArrayClass<DataType>::quicksort()
{
        _quicksort(0, size()-1);
        return;
}

//should return negative if item not found.
template <class DataType>
int ArrayClass<DataType>::_binarysearch(const DataType& data, int left, int right)
{
	int mid;
	int result;

	mid = (left+right)/2;
	if(left<right)
	{
		if(pointer_Object[mid]==data) 
			return mid;
		else if(pointer_Object[mid]<data)
			return _binarysearch(data, mid+1, right);
		else
			return _binarysearch(data, left, mid);
	}
	else
		if ((left==right) && (pointer_Object[left] == data))
			result = left;
		else
			result = -1;

	return result;
}

template <class DataType>
int ArrayClass<DataType>::binarysearch(const DataType& data)
{
	quicksort();
	return _binarysearch(data, 0, size()-1);
}

#endif
