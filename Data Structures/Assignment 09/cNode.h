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


#ifndef CNODE_H
#define CNODE_H

template< class T > class cLList;

template< class T >
class cNode
{
friend  class cLList< T >;

public:
	~cNode();

private:
	cNode(const T& init_data);
	cNode(const cNode< T >& copyme);

	T data;
	cNode< T >* next;
	cNode< T >* prev;

};

template< class T >
cNode< T >::cNode(const T& init_data)
		   :data(init_data), next(0), prev(0)
{
}

template< class T >
cNode< T >::cNode(const cNode< T >& copyme)
		   :data(copyme.data), next(copyme.next), prev(copyme.next)
{
}

template< class T >
cNode< T >::~cNode()
{
}

#endif