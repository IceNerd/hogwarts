/************************************************************************
* Class: tLList
*
* Constructors:	
*	tLList();
*	tLList(const tLList< T >& copyme);
*
* Mutators:
*	tLLNode< T >* getHead();
*	tLLNode< T >* getTail();
*
* Methods:
*	bool isEmpty() const;
*	const T& First() const;
*	const T& Last() const;
*	void Prepend(const T& init_data);
*	void Append(const T& init_data);
*	void Purge();
*	void Extract(const int& who);
*	void InsertAfter(const T& init_data, int after_who);
*	void InsertBefore(const T& init_data, int before_who);
*	void PrintForwards();
*	void PrintBackwards();
*	T& operator[](const int& who);
*	tLList< T >& operator=(const tLList< T >& copyme);
*
*************************************************************************/


#ifndef tLList_H
#define tLList_H

#include "tLLNode.h"
#include "Error.h"

template< class T >
class tLList
{public:
	tLList();
	tLList(const tLList< T >& copyme);
	~tLList();


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
	tLLNode< T >* getHead();
	tLLNode< T >* getTail();

	T& operator[](const int& who);
	tLList< T >& operator=(const tLList< T >& copyme);

private:
	tLLNode< T >* head;
	tLLNode< T >* tail;

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
bool tLList< T >::isEmpty() const
{
	bool temp(false);
	if((head == 0) || (tail == 0)) temp = true;
	return temp;
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
const T& tLList< T >::First() const
{
	if(head==0)
		throw EXCEPTION("const T& tLList< T >::First() const^List is empty^\n");
	return head->data;
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
const T& tLList< T >::Last() const
{
	if(tail==0)
		throw EXCEPTION("const T& tLList< T >::First() const^List is empty^\n");
	return tail->data;
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
void tLList< T >::Prepend(const T& init_data)
{
	if(isEmpty())
	{
		head = new tLLNode< T >(init_data);
		tail = head;
	}
	else
	{
		head->prev = new tLLNode< T >(init_data);
		head->prev->next = head;
		head = head->prev;
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
void tLList< T >::Append(const T& init_data)
{
	if(isEmpty())
	{
		tail = new tLLNode< T >(init_data);
		head = tail;
	}
	else
	{
		tail->next = new tLLNode< T >(init_data);
		tail->next->prev = tail;
		tail = tail->next;
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
void tLList< T >::Purge()
{
	if(!isEmpty())
	{
		tLLNode< T >* cursor = head;
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

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
void tLList< T >::Extract(const int& who)
{
	tLLNode< T >* cursor = head;
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
			throw EXCEPTION("void tLList< T >::Extract(int who)^Out of Bounds^");
		}
	}
	else
	{
		throw EXCEPTION("void tLList< T >::Extract(int who)^List is empty^");
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
void tLList< T >::InsertAfter(const T& init_data, int after_who)
{
	if(!isEmpty())
	{
		tLLNode< T >* cursor = head, * cursor2 = head;
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
			cursor->next = new tLLNode< T >(init_data);
			cursor2->prev = cursor->next;
			cursor->next->next = cursor2;
			cursor->next->prev = cursor;
		}
	}
	else
	{
		head = new tLLNode< T >(init_data);
		tail = head;
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
void tLList< T >::InsertBefore(const T& init_data, int before_who)
{
	if(!isEmpty())
	{
		tLLNode< T >* cursor = head, * cursor2 = head;
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
			cursor->next = new tLLNode< T >(init_data);
			cursor2->prev = cursor->next;
			cursor->next->next = cursor2;
			cursor->next->prev = cursor;
		}
	}
	else
	{
		head = new tLLNode< T >(init_data);
		tail = head;
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
void tLList< T >::PrintForwards()
{
	if(!isEmpty())
	{
		tLLNode< T >* cursor = head;
		cout<<"\nPrinting the list Forwards----\n";
		while(cursor!=tail)
		{
			cout<<cursor->data<<"\n";
			cursor = cursor->next;
		}
		cout<<cursor->data<<"\n";
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
void tLList< T >::PrintBackwards()
{
	if(!isEmpty())
	{
		tLLNode< T >* cursor = tail;
		cout<<"\nPrinting the list Backwards----\n";
		while(cursor!=head)
		{
			cout<<cursor->data<<"\n";
			cursor = cursor->prev;
		}
		cout<<cursor->data<<"\n";
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
tLLNode< T >* tLList< T >::getHead()
{
	return head;
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
tLLNode< T >* tLList< T >::getTail()
{
	return tail;
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
T& tLList< T >::operator[](const int& who)
{
	tLLNode< T >* cursor = head;

	if(!isEmpty())
	{

		int i(0);
		for(i = 0; (i < who) && (cursor != tail); i++)
		{
			cursor = cursor->next;
		}

		if(i != who)
		{
			throw EXCEPTION("T& tLList< T >::operator[](const int& who)^Out of bounds^\n");
		}
	}
	else
	{
		throw EXCEPTION("T& tLList< T >::operator[](const int& who)^List is empty^\n");
	}

	return cursor->data;
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
tLList< T >& tLList< T >::operator=(const tLList< T >& copyme)
{
	if(!isEmpty())
	{
		Purge();
	}

	if(!copyme.isEmpty())
	{
		tLLNode< T >* cursor = copyme.head;
		while(cursor != copyme.tail && copyme.tail != copyme.head)
		{
			Append(cursor->data);
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

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
tLList< T >::tLList()
:head(0), tail(0)
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
tLList< T >::tLList(const tLList< T >& copyme)
			:head(0), tail(0)
{
		*this = copyme;	
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
tLList< T >::~tLList()
{
		Purge();
}

#endif