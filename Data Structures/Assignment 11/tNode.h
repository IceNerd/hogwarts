/************************************************************************
* Class: tLList
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


#ifndef TNODE_H
#define TNODE_H

template< class T > class tLList;

template< class T >
class tNode
{
friend  class tLList< T >;

public:
	~tNode();

private:
	tNode(const T& init_data);
	tNode(const tNode< T >& copyme);

	T data;
	tNode< T >* next;
	tNode< T >* prev;

};

template< class T >
tNode< T >::tNode(const T& init_data)
		   :data(init_data), next(0), prev(0)
{
}

template< class T >
tNode< T >::tNode(const tNode< T >& copyme)
		   :data(copyme.data), next(copyme.next), prev(copyme.next)
{
}

template< class T >
tNode< T >::~tNode()
{
}

#endif