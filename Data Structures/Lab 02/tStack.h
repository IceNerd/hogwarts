/************************************************************************
* Class: tStack
*
* Constructors:	
*	tStack()
*
*	tStack(const tStack< T >&)
*
* Mutators:
*	tStack< T >& operator=(const tStack< T >&)
*
*	void Push(const T&)
*
*	void Pop()
*
* Methods:		
*	const T& Peek()
*
*	int Size()
*
*	bool isEmpty()
*
*************************************************************************/

#ifndef TSTACK_H
#define TSTACK_H

#include "tLList.h"
#include "tNode.h"
#include "cError.h"

template< class T >
class tStack
{public:
	tStack();
	~tStack();
	tStack(const tStack< T >&);

	tStack< T >& operator=(const tStack< T >&);
	void Push(const T&);
	void Pop();
	const T& Peek();
	int Size();
	bool isEmpty();

private:
	int stack_count;
	tLList< T > Array;

};

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
//Push - Pushes its parameter onto the top of the stack.
template< class T >
void tStack< T >::Push(const T& data)
{
		Array.Append(data);
		stack_count++;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
//Pop  - Removes the data from the top of the stack.  This method does not return the data element.
template< class T >
void tStack< T >::Pop()
{
	if(stack_count==0) 
	{
		throw EXCEPTION("void tStack< T >::Pop()^Underflow, cannot pop nothing^\n");
	}
	else
	{
		stack_count--;
		Array.Extract(stack_count);
	}
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
//Peek or Top - Returns the element on the top of the stack.
template< class T >
const T& tStack< T >::Peek()
{
	return Array.Last();
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
//Size – Returns the number of items currently on the stack.
template< class T >
int tStack< T >::Size()
{
	return stack_count;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
//isEmpty – Returns true if the stack is empty.
template< class T >
bool tStack< T >::isEmpty()
{
	if(stack_count == 0)
		return true;
	else
		return false;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tStack< T >& tStack< T >::operator=(const tStack< T >& copyme)
{
	Array = copyme.Array;
	stack_count = copyme.stack_count;
	return *this;
}

//-----CTors and DTors-------------------------

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tStack< T >::tStack()
			:stack_count(0)
{
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tStack< T >::~tStack()
{
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tStack< T >::tStack(const tStack< T >& copyme)
{
	*this = copyme;
}

#endif