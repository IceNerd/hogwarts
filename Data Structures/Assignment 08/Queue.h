#ifndef QUEUE_H
#define QUEUE_H

#include "Array.h"

template< class T >
class cQueue
{public:
	cQueue(const int&);
	~cQueue();
	cQueue(const cQueue< T > &);

	void Enqueue(const T&);
	void Dequeue();
	T& Front();
	int Size();
	bool isEmpty();
	bool isFull();

private:
	cArray< T > array;
	int queue_size;

};

//Enqueue - Puts the data item at the end (tail) of the queue.
template< class T >
void cQueue< T >::Enqueue(const T& data)
{
	if(queue_size == array.getLength())
	{
		throw EXCEPTION("void cQueue< T >::Enqueue(const T& data)^Queue Overflow^\n");
	}
	else
	{
		array[queue_size] = data;
		queue_size++;
	}
}

//Dequeue - Removes the data item at the front of the queue. This method does not return the data element.
template< class T >
void cQueue< T >::Dequeue()
{
	if(queue_size == 0)
	{
		throw EXCEPTION("void cQueue< T >::Dequeue()^Queue Underflow^\n");
	}
	else
	{
		queue_size--;
		for(int i = 0; i < queue_size; i++)
		{
			array[i] = array[i+1];
		}
	}
}

//Front - Returns a reference to the element at the front of the queue. This will allow the consumer to modify the element at the front of the queue.
template< class T >
T& cQueue< T >::Front()
{
	if(queue_size > 0)
	{
		return array[0];
	}
	else
	{
		throw EXCEPTION("T& cQueue< T >::Front()^No data available^\n");
	}
}

//Size – Returns the number of items currently in the queue.
template< class T >
int cQueue< T >::Size()
{
	return queue_size;
}

//isEmpty - Returns true if the stack is empty.
template< class T >
bool cQueue< T >::isEmpty()
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

//isFull - Returns true if the queue is full.
template< class T >
bool cQueue< T >::isFull()
{
	if(queue_size == array.getLength())
	{
		return true;
	}
	else
	{
		return false;
	}
}

template< class T >
cQueue< T >::cQueue(const int& init_size)
:array(init_size, 0), queue_size(0)
{
}

template< class T >
cQueue< T >::~cQueue()
{
}

template< class T >
cQueue< T >::cQueue(const cQueue< T >& copyme)
{
	array = copyme.array;
	queue_size = copyme.queue_size;
}

#endif