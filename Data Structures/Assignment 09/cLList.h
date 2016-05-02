/************************************************************************
* Class: cLList
*
* Constructors:	
*
*
* Mutators:
*
*
* Methods:		
*
*************************************************************************/


#ifndef CLLIST_H
#define CLLIST_H

#include "cNode.h"

template< class T >
class cLList
{public:
	cLList();
	cLList(const cLList< T >& copyme);
	~cLList();


	bool isEmpty() const;
	const T& First() const;
	const T& Last() const;
	void Prepend(const T& init_data);
	void Append(const T& init_data);
	void Purge();
	void Extract(const int& who);
	void InsertAfter(const T& init_data, int after_who);
	void InsertBefore(const T& init_data, int before_who);

	void PrintForwards();
	void PrintBackwards();
	cNode< T >* getHead();
	cNode< T >* getTail();

	T& operator[](const int& who);
	cLList< T >& operator=(const cLList< T >& copyme);

private:
	cNode< T >* head;
	cNode< T >* tail;

};

//isEmpty – does the list have any elements in it?
template< class T >
bool cLList< T >::isEmpty() const
{
	bool temp(false);
	if((head == 0) || (tail == 0)) temp = true;
	return temp;
}

//First – return a const reference to the first element.
template< class T >
const T& cLList< T >::First() const
{
	if(head==0)
		throw EXCEPTION("const T& cLList< T >::First() const^List is empty^\n");
	return head->data;
}

//Last – return a const reference to the last element.
template< class T >
const T& cLList< T >::Last() const
{
	if(tail==0)
		throw EXCEPTION("const T& cLList< T >::First() const^List is empty^\n");
	return tail->data;
}
//Prepend – add an item to the front of the list.
template< class T >
void cLList< T >::Prepend(const T& init_data)
{
	if(isEmpty())
	{
		head = new cNode< T >(init_data);
		tail = head;
	}
	else
	{
		head->prev = new cNode< T >(init_data);
		head->prev->next = head;
		head = head->prev;
	}
}

//Append – add an item to the end of the list.
template< class T >
void cLList< T >::Append(const T& init_data)
{
	if(isEmpty())
	{
		tail = new cNode< T >(init_data);
		head = tail;
	}
	else
	{
		tail->next = new cNode< T >(init_data);
		tail->next->prev = tail;
		tail = tail->next;
	}
}

//Purge – remove all items from the list.
template< class T >
void cLList< T >::Purge()
{
	if(!isEmpty())
	{
		cNode< T >* cursor = head;
		while(head->next)
		{
			head = head->next;
			delete cursor;
			cursor = head;
		}
		delete cursor;
		cursor = 0;
		head = 0;
		tail = 0;
	}
}

//Extract – remove a single item from the list.
template< class T >
void cLList< T >::Extract(const int& who)
{
	cNode< T >* cursor = head;
	if(!isEmpty())
	{
		int i(0);
		for(i = 0; (i < who) && (cursor != tail); i++)
		{
			cursor = cursor->next;
		}

		if(i == who)
		{
			if(tail != head)
			{
				if(cursor == tail)
				{
					cursor->prev->next = 0;
					tail = cursor->prev;
				}
				else if(cursor == head)
				{
					cursor->next->prev = 0;
					head = cursor->next;
				}
				else
				{
					cursor->next->prev = cursor->prev;
					cursor->prev->next = cursor->next;
				}

				delete cursor;
			}
			else
			{
				Purge();
			}
		}
		else
		{
			throw EXCEPTION("void cLList< T >::Extract(int who)^Out of Bounds^");
		}
	}
	else
	{
		throw EXCEPTION("void cLList< T >::Extract(int who)^List is empty^");
	}
}

//InsertAfter – insert an item after an item in the list.
template< class T >
void cLList< T >::InsertAfter(const T& init_data, int after_who)
{
	if(!isEmpty())
	{
		cNode< T >* cursor = head, * cursor2 = head;
		int i(0);
		for(i = 0; (i < after_who) && (cursor != tail); i++)
		{
			cursor = cursor->next;
		}

		if(cursor == head && i != after_who)
		{
			Prepend(init_data);
		}
		else if(cursor == tail)
		{
			Append(init_data);
		}
		else
		{
			cursor2 = cursor->next;
			cursor->next = new cNode< T >(init_data);
			cursor2->prev = cursor->next;
			cursor->next->next = cursor2;
			cursor->next->prev = cursor;
		}
	}
	else
	{
		head = new cNode< T >(init_data);
		tail = head;
	}
}

//InsertBefore – insert an item before an item in the list.
template< class T >
void cLList< T >::InsertBefore(const T& init_data, int before_who)
{
	if(!isEmpty())
	{
		cNode< T >* cursor = head, * cursor2 = head;
		int i(0);
		for(i = 0; (i < before_who) && (cursor != tail); i++)
		{
			cursor = cursor->next;
		}

		if(cursor == tail && i != before_who)
		{
			Append(init_data);
		}
		else if(cursor == head)
		{
			Prepend(init_data);
		}
		else
		{
			cursor2 = cursor;
			cursor = cursor->prev;
			cursor->next = new cNode< T >(init_data);
			cursor2->prev = cursor->next;
			cursor->next->next = cursor2;
			cursor->next->prev = cursor;
		}
	}
	else
	{
		head = new cNode< T >(init_data);
		tail = head;
	}
}

template< class T >
void cLList< T >::PrintForwards()
{
	if(!isEmpty())
	{
		cNode< T >* cursor = head;
		cout<<"\nPrinting the list Forwards----\n";
		while(cursor!=tail)
		{
			cout<<cursor->data<<"\n";
			cursor = cursor->next;
		}
		cout<<cursor->data<<"\n";
	}
}

template< class T >
void cLList< T >::PrintBackwards()
{
	if(!isEmpty())
	{
		cNode< T >* cursor = tail;
		cout<<"\nPrinting the list Backwards----\n";
		while(cursor!=head)
		{
			cout<<cursor->data<<"\n";
			cursor = cursor->prev;
		}
		cout<<cursor->data<<"\n";
	}
}

template< class T >
cNode< T >* cLList< T >::getHead()
{
	return head;
}

template< class T >
cNode< T >* cLList< T >::getTail()
{
	return tail;
}

template< class T >
T& cLList< T >::operator[](const int& who)
{
	cNode< T >* cursor = head;

	if(!isEmpty())
	{

		int i(0);
		for(i = 0; (i < who) && (cursor != tail); i++)
		{
			cursor = cursor->next;
		}

		if(i != who)
		{
			throw EXCEPTION("T& cLList< T >::operator[](const int& who)^Out of bounds^\n");
		}
	}
	else
	{
		throw EXCEPTION("T& cLList< T >::operator[](const int& who)^List is empty^\n");
	}

	return cursor->data;
}

template< class T >
cLList< T >& cLList< T >::operator=(const cLList< T >& copyme)
{
	if(!isEmpty())
	{
		Purge();
	}

	if(!copyme.isEmpty())
	{
		cNode< T >* cursor = copyme.head;
		while(cursor != copyme.tail && copyme.tail != copyme.head)
		{
			Append(cursor->data);
			cout<<cursor->data<<"\n";
			cursor = cursor->next;
		}
		Append(cursor->data);
	}
	else
	{
		head = 0;
		tail = 0;
	}

	return *this;
}


//-------------------------------------------------------------------
template< class T >
cLList< T >::cLList()
:head(0), tail(0)
{
}

template< class T >
cLList< T >::cLList(const cLList< T >& copyme)
			:head(0), tail(0)
{
		*this = copyme;	
}

template< class T >
cLList< T >::~cLList()
{
		Purge();
}

#endif