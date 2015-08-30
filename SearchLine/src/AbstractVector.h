
#ifndef _ABSTRACTVECTOR_H
#define _ABSTRACTVECTOR_H
#include "AbstractArray.h"

template <class DataType>
class AbstractVector : virtual public AbstractArrayClass<DataType>
{
public: 
	virtual void insert(const DataType& item, int index) = 0;
	virtual void remove(int index) = 0;
	virtual void add(const DataType& item) = 0;
};
#endif
