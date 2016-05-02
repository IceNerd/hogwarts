#ifndef THNODE_H
#define THNODE_H

template< class K, class V > class tHTable;
#include "tLLNode.h"

template< class K, class V >
class tHNode
{	friend class tHTable< K, V >;
	friend class tLLNode< tHNode >;

private:
	tHNode(K, V);
	~tHNode();

	K key;
	V value;

};

template< class K, class V >
tHNode< K, V >::tHNode(K init_key, V init_val)
:key(init_key), value(init_val)
{
}

template< class K, class V >
tHNode< K, V >::~tHNode()
{
}

#endif