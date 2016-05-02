/************************************************************************
* Class: tLLNode
*
* Constructors:	
*	tLLNode(const T& init_data);
*	tLLNode(const tLLNode< T >& copyme);
*
* Mutators:
*
*
* Methods:		
*
*************************************************************************/


#ifndef tLLNode_H
#define tLLNode_H

template< class T > class tLList;

template< class T >
class tLLNode
{
friend  class tLList< T >;

public:
	~tLLNode();

private:
	tLLNode(const T& init_data);
	tLLNode(const tLLNode< T >& copyme);

	T data;
	tLLNode< T >* next;
	tLLNode< T >* prev;

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
tLLNode< T >::tLLNode(const T& init_data)
		   :data(init_data), next(0), prev(0)
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
tLLNode< T >::tLLNode(const tLLNode< T >& copyme)
		   :data(copyme.data), next(copyme.next), prev(copyme.next)
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
tLLNode< T >::~tLLNode()
{
}

#endif