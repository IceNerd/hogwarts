/************************************************************************
* Class: Stack
*
* Constructors:
*	tStack();
*	tStack(const tStack< T >&);
*
* Mutators:
*	<none>
*
* Methods:
*	tStack< T >& operator=(const tStack< T >&);
*	void Push(const T&);
*	void Pop();
*	const T& Peek();
*	int Size();
*	bool isEmpty();
*
*************************************************************************/

#ifndef STACK_H
#define STACK_H

#include "tLList.h"
#include "tLLNode.h"

template< class T >
class tStack
{public:
	tStack();
	tStack(const tStack< T >&);
	~tStack();

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

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
void tStack< T >::Push(const T& data)
{
		Array.Append(data);
		stack_count++;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
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

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
const T& tStack< T >::Peek()
{
	return Array.Last();
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
int tStack< T >::Size()
{
	return stack_count;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
bool tStack< T >::isEmpty()
{
	if(stack_count == 0)
		return true;
	else
		return false;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
tStack< T >& tStack< T >::operator=(const tStack< T >& copyme)
{
	Array = copyme.Array;
	stack_count = copyme.stack_count;
	return *this;
}

//-----CTors and DTors-----------------------------------------

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
tStack< T >::tStack()
			:stack_count(0)
{
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
tStack< T >::~tStack()
{
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
tStack< T >::tStack(const tStack< T >& copyme)
{
	*this = copyme;
}

#endif