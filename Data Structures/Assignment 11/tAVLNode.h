/************************************************************************
* Class: tAVLNode
*
* Constructors:
*	tAVLNode(const T& init_data)
*
*	tAVLNode(const tAVLNode< T >& copyme)
*
* Mutators:
*	<none>
*
* Methods:
*	<none>
*
*************************************************************************/


#ifndef TAVLNode_H
#define TAVLNode_H

template< class T > class tAVL;

template< class T >
class tAVLNode
{
friend class tAVL< T >;

public:
	~tAVLNode();

private:
	tAVLNode(const T& init_data);
	tAVLNode(const tAVLNode< T >& copyme);

	T data;
	tAVLNode< T >* left;
	tAVLNode< T >* right;

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
tAVLNode< T >::tAVLNode(const T& init_data)
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
tAVLNode< T >::tAVLNode(const tAVLNode< T >& copyme)
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
tAVLNode< T >::~tAVLNode()
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