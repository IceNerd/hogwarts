/************************************************************************
* Class: tQueue
*
* Constructors:
*	tQueue();
*	tQueue(const tQueue< T > &);
*
* Mutators:
*	<none>
*
* Methods:
*	void Enqueue(const T&);
*	void Dequeue();
*	T& Front();
*	int Size();
*	bool isEmpty();
*
*************************************************************************/

#ifndef TQUEUE_H
#define TQUEUE_H

#include "tLList.h"

template< class T >
class tQueue
{public:
	tQueue();
	tQueue(const tQueue< T > &);
	~tQueue();

	void Enqueue(const T&);
	void Dequeue();
	T& Front();
	int Size();
	bool isEmpty();

private:
	tLList< T > array;
	int queue_size;

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
void tQueue< T >::Enqueue(const T& data)
{
	
		array.Append(data);
		queue_size++;
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
void tQueue< T >::Dequeue()
{
	if(queue_size == 0)
	{
		throw EXCEPTION("void tQueue< T >::Dequeue()^Queue Underflow^\n");
	}
	else
	{
		queue_size--;
		array.Extract(0);
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
T& tQueue< T >::Front()
{
	if(queue_size > 0)
	{
		return array[0];
	}
	else
	{
		throw EXCEPTION("T& tQueue< T >::Front()^No data available^\n");
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
int tQueue< T >::Size()
{
	return queue_size;
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
bool tQueue< T >::isEmpty()
{
	if(queue_size == 0)
	{
		return true;
	}
	else
	{
		return false;
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
tQueue< T >::tQueue()
			:queue_size(0)
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
tQueue< T >::~tQueue()
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
tQueue< T >::tQueue(const tQueue< T >& copyme)
{
	array = copyme.array;
	queue_size = copyme.queue_size;
}

#endif