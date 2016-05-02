/************************************************************************
* Class: tTreeNode
*
* Constructors:
*	tTreeNode(const T& init_data)
*	tTreeNode(const tTreeNode< T >& copyme)
*
* Mutators:
*	void setData(const T&);
*	T& getData();
*	void newright(tTreeNode< T >*, const T&);
*	void newleft(tTreeNode< T >*, const T&);
*	tTreeNode< T >* getparent();
*	tTreeNode< T >* getleft();
*	tTreeNode< T >* getright();
*
* Methods:
*	<none>
*
*************************************************************************/


#ifndef tTreeNode_H
#define tTreeNode_H

template< class T > class tThrTree;

template< class T >
class tTreeNode
{
friend class tThrTree< T >;

public:
	~tTreeNode();

	void setData(const T&);
	T& getData();
	void newright(tTreeNode< T >*, const T&);
	void newleft(tTreeNode< T >*, const T&);
	tTreeNode< T >* getparent();
	tTreeNode< T >* getleft();
	tTreeNode< T >* getright();

private:
	tTreeNode(const T& init_data);
	tTreeNode(const tTreeNode< T >& copyme);

	T data;
	tTreeNode< T >* parent;
	tTreeNode< T >* left;
	tTreeNode< T >* right;

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
tTreeNode< T >* tTreeNode< T >::getparent()
{
	return parent;
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
void tTreeNode< T >::newright(tTreeNode< T >* pptr, const T& newNode)
{
	right = new tTreeNode< T >(newNode);
	right->parent = pptr;
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
void tTreeNode< T >::newleft(tTreeNode< T >* pptr, const T& newNode)
{
	left = new tTreeNode< T >(newNode);
	left->parent = pptr;
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
void tTreeNode< T >::setData(const T& toThis)
{
	data = toThis;
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
T& tTreeNode< T >::getData()
{
	return data;
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
tTreeNode< T >* tTreeNode< T >::getleft()
{
	return left;
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
tTreeNode< T >* tTreeNode< T >::getright()
{
	return right;
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
tTreeNode< T >::tTreeNode(const T& init_data)
		   :data(init_data), left(0), right(0), parent(0)
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
tTreeNode< T >::tTreeNode(const tTreeNode< T >& copyme)
		   :data(copyme.data), left(copyme.left), right(copyme.right), parent(copyme.parent)
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
tTreeNode< T >::~tTreeNode()
{
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