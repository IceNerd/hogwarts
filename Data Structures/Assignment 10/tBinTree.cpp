#include "tBinTree.h"

//Insert – Write both recursive and iterative versions.
//Inserts a Node recursively
template< class T >
void tBinTree< T >::Recursive_Insert(const T& data)
{
}

//Inserts a Node Iteratively
template< class T >
void tBinTree< T >::Iterative_Insert(const T& data)
{
	if(root == 0)
	{
		root = new tNode< T >(data);
	}
	else
	{
		tNode< T >* cursor(root);
		bool foundplace(false);

		while(!foundplace)
		{
			if(data < cursor->data)
			{
				if(cursor->left == 0)
				{
					cursor->left = new tNode< T >(data);
					foundplace = true;
				}
				else
				{
					cursor = cursor->left;
				}
			}
			else if(data > cursor ->data)
			{
				if(cursor->right == 0)
				{
					cursor->right = new tNode< T >(data);
					foundplace = true;
				}
				else
				{
					cursor = cursor->right;
				}
			}
			else
			{
				foundplace = true;
				throw EXCEPTION("void tBinTree< T >::Iterative_Insert(const T& data)^error^");
			}
		}
		
	}
}

//Delete  – Write both recursive and iterative versions.
//Deletes Recursively
template< class T >
void tBinTree< T >::Recursive_Delete()
{
}

//Deletes Iteratively
template< class T >
void tBinTree< T >::Iterative_Delete()
{
}


//Traversals – Write In-Order, Post-Order, Pre-Order and Breadth-First traversals.
//In-Order Traversal
template< class T >
void tBinTree< T >::IO_Traverse()
{
}

//Post-Order Traversal
template< class T >
void tBinTree< T >::PO_Traverse()
{
}

//Pre-order Traversal
template< class T >
void tBinTree< T >::PrO_Traverse()
{
}


//Purge – Destroy the tree.
template< class T >
void tBinTree< T >::Purge()
{
}

//Height – Find the height of the tree.
template< class T >
int tBinTree< T >::Height()
{
}

template< class T >
tBinTree< T >& tBinTree< T >::operator=(const tBinTree< T >& copyme)
{
	root = copyme.root;
	return *this;
}

//---------- Ctors and Dtors -------------------
template< class T >
tBinTree< T >::tBinTree()
			  :root(0)
{
}

template< class T >
tBinTree< T >::tBinTree(const tBinTree< T >& copyme)
			  :root(copyme.root)
{
}

template< class T >
tBinTree< T >::~tBinTree()
{
	if(root != 0)
	{
		delete root;
	}
	root = 0;
}
