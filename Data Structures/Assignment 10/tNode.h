/************************************************************************
* Class: tNode
*
* Constructors:
*	tNode(const T& init_data)
*
*	tNode(const tNode< T >& copyme)
*
* Mutators:
*	<none>
*
* Methods:
*	<none>
*
*************************************************************************/


#ifndef TNODE_H
#define TNODE_H

template< class T > class tBinTree;

template< class T >
class tNode
{
friend class tBinTree< T >;

public:
	~tNode();

private:
	tNode(const T& init_data);
	tNode(const tNode< T >& copyme);

	T data;
	tNode< T >* left;
	tNode< T >* right;

};

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tNode< T >::tNode(const T& init_data)
		   :data(init_data), left(0), right(0)
{
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tNode< T >::tNode(const tNode< T >& copyme)
		   :data(copyme.data), left(copyme.left), right(copyme.right)
{
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tNode< T >::~tNode()
{
	cout<<data<<" deleted\n";
	if(left != 0)
	{
		delete left;
	}

	if(right != 0)
	{
		delete right;
	}
}

#endif