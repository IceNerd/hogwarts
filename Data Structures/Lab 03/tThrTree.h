/************************************************************************
* Class: tThrTree
*
* Constructors:
*	tThrTree();
*	tThrTree(const tThrTree&);
*
* Mutators:
*	tTreeNode< T >* getRoot();
*
* Methods:
*	void Insert(const T&);
*	void Delete( const T&);
*	void Purge();
*	int Height();
*	void IO_Traverse( void(*fun_ptr)(const T&) );
*	void PO_Traverse( void(*fun_ptr)(const T&) );
*	void PrO_Traverse( void(*fun_ptr)(const T&) );
*	void BF_Traverse( void(*fun_ptr)(const T&) );
*
*************************************************************************/

#ifndef tThrTree_H
#define tThrTree_H

#include "tTreeNode.h"
#include "tQueue.h"

template< class T >
class tThrTree
{
	public:
		tThrTree();
		tThrTree(const tThrTree&);
		~tThrTree();
		tThrTree& operator=(const tThrTree&);

		void Insert(const T&);
		void Delete( const T&);
		void Purge();
		int Height();

		void IO_Traverse( void(*fun_ptr)(const T&) );
		void PO_Traverse( void(*fun_ptr)(const T&) );
		void PrO_Traverse( void(*fun_ptr)(const T&) );
		void BF_Traverse( void(*fun_ptr)(const T&) );
		tTreeNode< T >* getRoot();

	private:
		int Height(const tTreeNode< T >*, int = 0);
		void IO_Traverse( void(*fun_ptr)(const T&), const tTreeNode< T >* );
		void PO_Traverse( void(*fun_ptr)(const T&), const tTreeNode< T >* );
		void PrO_Traverse( void(*fun_ptr)(const T&), const tTreeNode< T >* );

		tTreeNode< T >* root;
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
tTreeNode< T >* tThrTree< T >::getRoot()
{
	return root;
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
void tThrTree< T >::Insert(const T& data)
{
	if(root == 0)
	{
		root = new tTreeNode< T >(data);
	}
	else
	{
		tTreeNode< T >* cursor(root);
		bool foundplace(false);

		while(!foundplace)
		{
			if(data < cursor->data)
			{
				if(cursor->left == 0)
				{
					cursor->left = new tTreeNode< T >(data);
					cursor->left->parent = cursor;
					foundplace = true;
				}
				else
				{
					cursor = cursor->left;
				}
			}
			else if(data > cursor->data)
			{
				if(cursor->right == 0)
				{
					cursor->right = new tTreeNode< T >(data);
					cursor->right->parent = cursor;
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
				throw EXCEPTION("void tThrTree< T >::Insert(const T& data)^Data already in Tree^");
			}
		}
		
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
void tThrTree< T >::Delete(const T& what)
{
	tTreeNode< T >* cursor;
	tTreeNode< T >* trail_cursor;
	bool L_or_R(false); //false = left; true = right;
	cursor = root;
	trail_cursor = cursor;
	//find the node ( or is it even there? )
	while( (cursor->data != what) && (cursor != 0) )
	{
		if(what > cursor->data)
		{
			if(cursor->right)
			{
				trail_cursor = cursor;
				cursor = cursor->right;
				L_or_R = true;
			}
			else
			{
				throw EXCEPTION("void tThrTree< T >::Delete(const T& what)^Data not found^\n");
			}
		}
		else if(what < cursor->data)
		{
			if(cursor->left)
			{
				trail_cursor = cursor;
				cursor = cursor->left;
				L_or_R = false;
			}
			else
			{
				throw EXCEPTION("void tThrTree< T >::Delete(const T& what)^Data not found^\n");
			}
		}
	}


	if(cursor->data == what)
	{
		//case 1
		if( (cursor->left == 0) && (cursor->right == 0) )
		{
			if(L_or_R)
			{
				trail_cursor->right = 0;
			}
			else
			{
				trail_cursor->left = 0;
			}
			delete cursor;
		}
		//case 2
		else if( (cursor->left == 0) && (cursor->right) )
		{
			if(L_or_R)
			{
				trail_cursor->right = cursor->right;
				trail_cursor->right->parent = trail_cursor;
				cursor->right = 0;
				delete cursor;
			}
			else
			{
				trail_cursor->left = cursor->right;
				trail_cursor->left->parent = trail_cursor;
				cursor->right = 0;
				delete cursor;
			}
		}
		//case 3
		else if( (cursor->left) && (cursor->right == 0) )
		{
			if(L_or_R)
			{
				trail_cursor->right = cursor->left;
				trail_cursor->right->parent = trail_cursor;
				cursor->left = 0;
				delete cursor;
			}
			else
			{
				trail_cursor->left = cursor->left;
				trail_cursor->left->parent = trail_cursor;
				cursor->left = 0;
				delete cursor;
			}
		}
		//case 4
		else
		{
			tTreeNode< T >* right_most;
			right_most = cursor->left;
			while(right_most->right)
			{
				right_most = right_most->right;
			}
			tTreeNode< T >* left_most;
			left_most = right_most;
			while(left_most->left)
			{
				left_most = left_most->left;
			}

			if(L_or_R)
			{
				trail_cursor->right = right_most;
			}
			else
			{
				trail_cursor->left = right_most;
			}
			left_most->left = cursor->left;
			right_most->right = cursor->right;
			cursor->right = 0;
			cursor->left = 0;
			delete cursor;
		}
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
void tThrTree< T >::IO_Traverse(void(*fun_ptr)(const T& data))
{
	IO_Traverse(fun_ptr, root);
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
void tThrTree< T >::IO_Traverse(void(*fun_ptr)(const T& data), const tTreeNode< T >* parent)
{
	if(parent)
	{
		IO_Traverse(fun_ptr, parent->left);
		fun_ptr(parent->data);
		IO_Traverse(fun_ptr, parent->right);
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
void tThrTree< T >::PO_Traverse(void(*fun_ptr)(const T& data))
{
	PO_Traverse(fun_ptr, root);
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
void tThrTree< T >::PO_Traverse(void(*fun_ptr)(const T& data), const tTreeNode< T >* parent)
{
if(parent)
	{
		PO_Traverse(fun_ptr, parent->left);
		PO_Traverse(fun_ptr, parent->right);
		fun_ptr(parent->data);
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
void tThrTree< T >::PrO_Traverse(void(*fun_ptr)(const T& data))
{
	PrO_Traverse(fun_ptr, root);
}

template< class T >
void tThrTree< T >::PrO_Traverse(void(*fun_ptr)(const T& data), const tTreeNode< T >* parent)
{
	if(parent)
	{
		fun_ptr(parent->data);
		PrO_Traverse(fun_ptr, parent->left);
		PrO_Traverse(fun_ptr, parent->right);
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
void tThrTree< T >::BF_Traverse( void(*fun_ptr)(const T& data) )
{
	tQueue< tTreeNode< T >* > BF_Q;
	if(root)
	{
		BF_Q.Enqueue(root);
		int SO_LL(0);
		while(!BF_Q.isEmpty())
		{
			SO_LL = BF_Q.Size();
			for(int i = 0; i < SO_LL; i++)
			{
				if(BF_Q.Front())
				{
					fun_ptr(BF_Q.Front()->data);
					if(BF_Q.Front()->left)
					{
						BF_Q.Enqueue(BF_Q.Front()->left);
					}
					if(BF_Q.Front()->right)
					{
						BF_Q.Enqueue(BF_Q.Front()->right);
					}
				}
				BF_Q.Dequeue();
			}
		}
	}
	else
	{
		throw EXCEPTION("void tThrTree< T >::BF_Traverse( void(*fun_ptr)(const T& data) )^no data^");
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
void tThrTree< T >::Purge()
{
	delete root;
	root = 0;
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
int tThrTree< T >::Height()
{
	if(root == 0)
	{
		return 0;
	}
	else
	{
		return Height(root, 1);
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
int tThrTree< T >::Height(const tTreeNode< T >* top, int current_height)
{
	int left_height(0);
	int right_height(0);
	int total_height(current_height);

	if(top != root)
	{
		current_height++;
	}
	total_height = current_height;

	if(top->left)
	{
		left_height = Height(top->left, current_height);
	}

	if(top->right)
	{
		right_height = Height(top->right, current_height);
	}

	if( (left_height != 0) || (right_height != 0) ) 
    { 
        if(left_height > right_height) 
		{
            total_height = left_height; 
		}
        else if(right_height >= left_height) 
		{
            total_height = right_height; 
		}
    } 

      return total_height; 
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
tThrTree< T >& tThrTree< T >::operator=(const tThrTree< T >& copyme)
{
	tQueue< tTreeNode< T >* > copy_Q;
	tQueue< tTreeNode< T >* > parent_Q;
	int level_size(0);

	if(copyme.root)
	{
		copy_Q.Enqueue(copyme.root);
		int copy_count(0);
		root = new tTreeNode< T >(*copy_Q.Front());
		parent_Q.Enqueue(root);
		
		while(!copy_Q.isEmpty())
		{
			level_size = copy_Q.Size();
			for(int i = 0; i < level_size; i++)
			{

				if( copy_Q.Front()->left )
				{
					copy_Q.Enqueue(copy_Q.Front()->left);
					parent_Q.Front()->left = new tTreeNode< T >(*copy_Q.Front()->left);
					parent_Q.Enqueue(parent_Q.Front()->left);
				}
				if( copy_Q.Front()->right )
				{
					copy_Q.Enqueue(copy_Q.Front()->right);
					parent_Q.Front()->right = new tTreeNode< T >(*copy_Q.Front()->right);
					parent_Q.Enqueue(parent_Q.Front()->right);
				}

				copy_Q.Dequeue();
				parent_Q.Dequeue();
			}
		}
	}
	
	return *this;
}

//---------- Ctors and Dtors ----------------------------------


/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
template< class T >
tThrTree< T >::tThrTree()
			  :root(new tTreeNode< T >(0))
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
tThrTree< T >::tThrTree(const tThrTree< T >& copyme)
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
tThrTree< T >::~tThrTree()
{
	if(root != 0)
	{
		delete root;
	}
	root = 0;
}

#endif