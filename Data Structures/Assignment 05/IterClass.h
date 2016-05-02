#ifndef ITERCLASS_H
#define ITERCLASS_H

#include "Iterator.h"
#include "cLList.h"

template< class T >
class IterClass : public Iterator< T >
{public:
	IterClass(cLList< T >& list);
	~IterClass();
	IterClass(const IterClass< T >& copyme);
	IterClass< T >& operator=(const IterClass< T >& copyme);

	//Required BASE class methods
	void removeCurrent();
	void addBefore(T init_data);
	void addAfter(T init_data);
	virtual void Reset();
	virtual void operator=(T new_data);
	virtual T operator*();
	virtual T operator++();
	virtual bool operator!();
	virtual bool IsDone();

private:
	cNode< T >* cursor;
	cLList< T >& l_list;

};

template< class T >
void IterClass< T >::removeCurrent()
{
	cNode< T >* scout = cursor;
	int i(0);
	while(scout->prev != 0)
	{
		scout = scout->prev;
		i++;
	}
	l_list.Extracr(i);
}

template< class T >
void IterClass< T >::addBefore(T init_data)
{
	l_list.Prepend(init_data);
}

template< class T >
void IterClass< T >::addAfter(T init_data)
{
	l_list.Append(init_data);
}

//----------Virtuals
template< class T >
void IterClass< T >::Reset()
{
	cursor = l_list.getHead();
}

template< class T >
void IterClass< T >::operator=(T new_data)
{
	cursor->setData(new_data);
}

template< class T >
T IterClass< T >::operator*()
{
	return cursor->getData();
}

template< class T >
T IterClass< T >::operator++() 
{
	if(cursor != l_list.getTail())
	{
		cursor = cursor->getNext();
	}
	return cursor->getData();
}

template< class T >
bool IterClass< T >::operator!()
{
	bool temp(false);

	if(cursor->getNext())
	{
		temp = true;
	}
	else
	{
		cursor = l_list.getHead();
	}
	return temp;
}

template< class T >
bool IterClass< T >::IsDone()
{
	bool temp(false);

	if(cursor->getNext() == l_list.getTail()) temp = true;
	return temp;
}

//----op=
template< class T >
IterClass< T >& IterClass< T >::operator=(const IterClass< T >& copyme)
{
	cursor = copyme.cursor;
	l_list = copyme.l_list;
}

//---------CTors and DTors
template< class T >
IterClass< T >::IterClass(cLList< T >& copy_list)
			   :l_list(copy_list)
{
	cursor = copy_list.getHead();
}

template< class T >
IterClass< T >::~IterClass()
{

}

template< class T >
IterClass< T >::IterClass(const IterClass< T >& copyme)
			   :l_list(copyme.l_list), cursor(copyme.cursor)
{

}

#endif