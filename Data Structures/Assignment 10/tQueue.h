#ifndef TQUEUE_H
#define TQUEUE_H

#include "tLList.h"

template< class T >
class tQueue
{public:
	tQueue();
	~tQueue();
	tQueue(const tQueue< T > &);

	void Enqueue(const T&);
	void Dequeue();
	T& Front();
	int Size();
	bool isEmpty();

private:
	tLList< T > array;
	int queue_size;

};

//Enqueue - Puts the data item at the end (tail) of the queue.
template< class T >
void tQueue< T >::Enqueue(const T& data)
{
	
		array.Append(data);
		queue_size++;
}

//Dequeue - Removes the data item at the front of the queue. This method does not return the data element.
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

//Front - Returns a reference to the element at the front of the queue. This will allow the consumer to modify the element at the front of the queue.
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

//Size – Returns the number of items currently in the queue.
template< class T >
int tQueue< T >::Size()
{
	return queue_size;
}

//isEmpty - Returns true if the stack is empty.
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

template< class T >
tQueue< T >::tQueue()
			:queue_size(0)
{
}

template< class T >
tQueue< T >::~tQueue()
{
}

template< class T >
tQueue< T >::tQueue(const tQueue< T >& copyme)
{
	array = copyme.array;
	queue_size = copyme.queue_size;
}

#endif