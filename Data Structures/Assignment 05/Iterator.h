#ifndef ITERATOR_H
#define ITERATOR_H

template< class T >
class Iterator
{
	//Reset the pointer to the beginning
	virtual void Reset() = 0;
	//Have we reached the end of the list
	virtual bool IsDone() = 0;
	//Test if there is a current element
	virtual bool operator ! ()= 0;
	//Get current element
	virtual T operator * () = 0;
	//Get the next element
	virtual T operator ++ () = 0;
	//Change current element
	virtual void operator = (T newValue) = 0;
};

#endif