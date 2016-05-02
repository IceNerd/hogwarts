#ifndef STACK_H
#define STACK_H

#include "cLList.h"
#include "cNode.h"

template< class T >
class cStack
{public:
	cStack();
	~cStack();
	cStack(const cStack< T >&);

	cStack< T >& operator=(const cStack< T >&);
	void Push(const T&);
	void Pop();
	const T& Peek();
	int Size();
	bool isEmpty();

private:
	int stack_count;
	cLList< T > Array;

};

//Push - Pushes its parameter onto the top of the stack.
template< class T >
void cStack< T >::Push(const T& data)
{
		Array.Append(data);
		stack_count++;
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
		Array.Extract(stack_count);
	}
}

//Peek or Top - Returns the element on the top of the stack.
template< class T >
const T& cStack< T >::Peek()
{
	return Array.Last();
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

template< class T >
cStack< T >& cStack< T >::operator=(const cStack< T >& copyme)
{
	Array = copyme.Array;
	stack_count = copyme.stack_count;
	return *this;
}

//-----CTors and DTors-------------------------
template< class T >
cStack< T >::cStack()
			:stack_count(0)
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