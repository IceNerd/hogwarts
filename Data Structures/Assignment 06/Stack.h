#ifndef STACK_H
#define STACK_H

#include "Array.h"

template< class T >
class cStack
{public:
	cStack(const int&);
	~cStack();
	cStack(const cStack< T >&);

	cStack< T >& operator=(const cStack< T >&);
	void Push(const T&);
	void Pop();
	T& Peek();
	int Size();
	bool isEmpty();
	bool isFull();

private:
	int stack_count;
	cArray< T > Array;

};

//Push - Pushes its parameter onto the top of the stack.
template< class T >
void cStack< T >::Push(const T& data)
{
	if(Array.getLength() == stack_count)
	{
		throw EXCEPTION("void cStack< T >::Push(const T& data)^Stack Overflow^\n");
	}
	else
	{
		Array[stack_count] = data;
		stack_count++;
	}
}

//Pop  - Removes the data from the top of the stack.  This method does not return the data element.
template< class T >
void cStack< T >::Pop()
{
	if(stack_count==0) 
	{
		throw EXCEPTION("void cStack< T >::Pop()^Underflow, cannot pop nothing^\n");
	}
	else
	{
		stack_count--;
		Array[stack_count] = 0;
	}
}

//Peek or Top - Returns the element on the top of the stack.
template< class T >
T& cStack< T >::Peek()
{
	return Array[stack_count-1];
}

//Size – Returns the number of items currently on the stack.
template< class T >
int cStack< T >::Size()
{
	return stack_count;
}

//isEmpty – Returns true if the stack is empty.
template< class T >
bool cStack< T >::isEmpty()
{
	if(stack_count == 0)
		return true;
	else
		return false;
}

//isFull – Returns true if the stack is full.
template< class T >
bool cStack< T >::isFull()
{
	if(Array.getLength() == stack_count)
		return true;
	else
		return false;
}

template< class T >
cStack< T >& cStack< T >::operator=(const cStack< T >& copyme)
{
	Array = copyme.Array;
	stack_count = copyme.stack_count;
	return *this;
}

//-----CTors and DTors-------------------------
template< class T >
cStack< T >::cStack(const int& init_size)
			:Array(init_size, 0), stack_count(0)
{
}

template< class T >
cStack< T >::~cStack()
{
}

template< class T >
cStack< T >::cStack(const cStack< T >& copyme)
{
	*this = copyme;
}

#endif