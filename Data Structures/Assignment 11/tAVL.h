#ifndef TAVL_H
#define TAVL_H

#include "tAVLNode.h"
#include "tQueue.h"

template< class T >
class tAVL
{
	public:
		tAVL();
		tAVL(const tAVL&);
		~tAVL();
		tAVL& operator=(const tAVL&);

		//Insert – Write both recursive and iterative versions.
		//Inserts a Node recursively
		void Recursive_Insert(const T&);
		
		//Inserts a Node Iteratively
		void Iterative_Insert(const T&);

		//Delete  – Write both recursive and iterative versions.
		//Deletes Recursively
		void Recursive_Delete(const T&);

		//Deletes Iteratively
		void Iterative_Delete( const T&);


		//Traversals – Write In-Order, Post-Order, Pre-Order and Breadth-First traversals.
		//In-Order Traversal
		void IO_Traverse( void(*fun_ptr)(const T&) );

		//Post-Order Traversal
		void PO_Traverse( void(*fun_ptr)(const T&) );

		//Pre-order Traversal
		void PrO_Traverse( void(*fun_ptr)(const T&) );

		//Breadth-First Traversal
		void BF_Traverse( void(*fun_ptr)(const T&) );


		//Purge – Destroy the tree.
		void Purge();

		//Height – Find the height of the tree.
		int Height();

		void Balance();


	private:
		void PRecursive_Insert(tAVLNode< T >*, const T&);
		void PRecursive_Delete(tAVLNode< T >*, const T&);

		void IO_Traverse( void(*fun_ptr)(const T&), const tAVLNode< T >* );
		void PO_Traverse( void(*fun_ptr)(const T&), const tAVLNode< T >* );
		void PrO_Traverse( void(*fun_ptr)(const T&), const tAVLNode< T >* );
		int Height(const tAVLNode< T >*, int = 0);

		int BalanceFactor(const tAVLNode< T >*);
		void LLRotate(tAVLNode< T >*);
		void RRRotate(tAVLNode< T >*&);

		tAVLNode< T >* root;

};

//Insert – Write both recursive and iterative versions.
//Inserts a Node recursively
template< class T >
void tAVL< T >::Recursive_Insert(const T& data)
{
	if(root == 0)
	{
		root = new tAVLNode< T >(data);
	}
	else
	{
		PRecursive_Insert(root, data);
	}
}

template< class T >
void tAVL< T >::PRecursive_Insert(tAVLNode< T >* cursor, const T& data)
{
	if(data < cursor->data)
	{
		if(cursor->left == 0)
		{
			cursor->left = new tAVLNode< T >(data);
		}
		else
		{
			PRecursive_Insert(cursor->left, data);
		}
	}
	else if(data > cursor->data)
	{
		if(cursor->right == 0)
		{
			cursor->right = new tAVLNode< T >(data);
		}
		else
		{
			PRecursive_Insert(cursor->right, data);
		}
	}
}

//Inserts a Node Iteratively
template< class T >
void tAVL< T >::Iterative_Insert(const T& data)
{
	if(root == 0)
	{
		root = new tAVLNode< T >(data);
	}
	else
	{
		tAVLNode< T >* cursor(root);
		bool foundplace(false);

		while(!foundplace)
		{
			if(data < cursor->data)
			{
				if(cursor->left == 0)
				{
					cursor->left = new tAVLNode< T >(data);
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
					cursor->right = new tAVLNode< T >(data);
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
				throw EXCEPTION("void tAVL< T >::Iterative_Insert(const T& data)^Data already in Tree^");
			}
		}
		
	}
}

//Delete  – Write both recursive and iterative versions.
//Deletes Recursively
template< class T >
void tAVL< T >::Recursive_Delete(const T& what)
{
	if(root == 0)
	{
		throw EXCEPTION("void tAVL< T >::Recursive_Delete()^No data to delete^\n");
	}
	else
	{
		if(root->data == what)
		{	
			if(root->left)
			{
				tAVLNode< T >* right_most;
				right_most = root->left;
				while(right_most->right)
				{
					right_most = right_most->right;
				}
				right_most->right = root->right;
				right_most = root->left;
				root->right = 0;
				root->left = 0;
				delete root;
				root = right_most;
			}
			else
			{
				tAVLNode< T >* cursor;
				cursor = root;
				if(cursor->right)
				{
					cursor = cursor->right;
					root->left = 0;
					root->right = 0;
					delete root;
					root = cursor;
				}
				else
				{
					delete root;
				}
			}
		}
		else
		{
			PRecursive_Delete(root, what);
		}
	}
}

template< class T >
void tAVL< T >::PRecursive_Delete(tAVLNode< T >* currnode, const T& what)
{
	tAVLNode< T >* target;
	target = 0;
	bool LorR(false);
	if(currnode->left)
	{
		if(currnode->left->data == what)
		{
			LorR = false;
			target = currnode->left;
		}
	}
	if(currnode->right)
	{
		if(currnode->right->data == what)
		{
			target = currnode->right;
			LorR = true;
		}
	}

	if(target)
	{
		//case 1
		if( (target->left == 0) && (target->right == 0) )
		{
			if(LorR)
			{
				currnode->right = 0;
			}
			else
			{
				currnode->left = 0;
			}
			delete target;
		}
		//case 2 (empty left subtree; non-empty right subtree)
		else if( (target->left == 0) && (target->right != 0) )
		{
			if(LorR)
			{
				currnode->right = target->right;
			}
			else
			{
				currnode->left = target->right;
			}
			target->left = 0;
			target->right = 0;
			delete target;
		}
		//case 3 (empty right subtree and a non-empty left subtree.
		else if( (target->right == 0) && (target->left != 0) )
		{
			if(LorR)
			{
				currnode->right = target->left;
			}
			else
			{
				currnode->left = target->left;
			}
			target->left = 0;
			target->right = 0;
			delete target;
		}
		//case 4
		else
		{
			//find right-most child of the left subtree
			tAVLNode< T >* cursor;
			tAVLNode< T >* trail_cursor;
			cursor = target;
			trail_cursor = cursor;
			while(cursor->right)
			{
				trail_cursor = cursor;
				cursor = cursor->right;
			}
			trail_cursor->right = 0;

			//Exchange that node with the one to be deleted
			//find left-most
			tAVLNode< T >* left_cursor;
			left_cursor = cursor;
			while(left_cursor->left)
			{
				left_cursor = left_cursor->left;
			}

			//now place this chunk in place of the target
			if(LorR)
			{
				currnode->right = cursor;
			}
			else
			{
				currnode->left = cursor;
			}
			cursor->right = target->right;
			left_cursor->left = target->left;
			target->left = 0;
			target->right = 0;
			delete target;
		}

	}
	else
	{
		if( (currnode->left == 0) && (currnode->right == 0) )
		{
			throw EXCEPTION("void tAVL< T >::PRecursive_Delete(tAVLNode< T >* currnode, const T& what)^Node not found^\n");
		}
		else
		{
			if( (what < currnode->data) && (currnode->left) )
			{
				cout<<"Left\n";
				PRecursive_Delete(currnode->left, what);
			}
			else if( (what < currnode->data) && (currnode->left == 0) )
			{
				throw EXCEPTION("void tAVL< T >::PRecursive_Delete(tAVLNode< T >* currnode, const T& what)^Node not found^\n");
			}
			else if( (what > currnode->data) && (currnode->right) )
			{
				cout<<"Right\n";
				PRecursive_Delete(currnode->right, what);
			}
			else if( (what > currnode->data) && (currnode->right == 0) )
			{
				throw EXCEPTION("void tAVL< T >::PRecursive_Delete(tAVLNode< T >* currnode, const T& what)^Node not found^\n");
			}
		}
	}
}

//Deletes Iteratively
template< class T >
void tAVL< T >::Iterative_Delete(const T& what)
{
	tAVLNode< T >* cursor;
	tAVLNode< T >* trail_cursor;
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
				throw EXCEPTION("void tAVL< T >::Iterative_Delete(const T& what)^Data not found^\n");
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
				throw EXCEPTION("void tAVL< T >::Iterative_Delete(const T& what)^Data not found^\n");
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
				cursor->right = 0;
				delete cursor;
			}
			else
			{
				trail_cursor->left = cursor->right;
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
				cursor->left = 0;
				delete cursor;
			}
			else
			{
				trail_cursor->left = cursor->left;
				cursor->left = 0;
				delete cursor;
			}
		}
		//case 4
		else
		{
			tAVLNode< T >* right_most;
			right_most = cursor->left;
			while(right_most->right)
			{
				right_most = right_most->right;
			}
			tAVLNode< T >* left_most;
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


//Traversals – Write In-Order, Post-Order, Pre-Order and Breadth-First traversals.
//In-Order Traversal
template< class T >
void tAVL< T >::IO_Traverse(void(*fun_ptr)(const T& data))
{
	IO_Traverse(fun_ptr, root);
}

template< class T >
void tAVL< T >::IO_Traverse(void(*fun_ptr)(const T& data), const tAVLNode< T >* parent)
{
	if(parent)
	{
		IO_Traverse(fun_ptr, parent->left);
		fun_ptr(parent->data);
		IO_Traverse(fun_ptr, parent->right);
	}
}

//Post-Order Traversal
template< class T >
void tAVL< T >::PO_Traverse(void(*fun_ptr)(const T& data))
{
	PO_Traverse(fun_ptr, root);
}

template< class T >
void tAVL< T >::PO_Traverse(void(*fun_ptr)(const T& data), const tAVLNode< T >* parent)
{
if(parent)
	{
		PO_Traverse(fun_ptr, parent->left);
		PO_Traverse(fun_ptr, parent->right);
		fun_ptr(parent->data);
	}
}

//Pre-order Traversal
template< class T >
void tAVL< T >::PrO_Traverse(void(*fun_ptr)(const T& data))
{
	PrO_Traverse(fun_ptr, root);
}

template< class T >
void tAVL< T >::PrO_Traverse(void(*fun_ptr)(const T& data), const tAVLNode< T >* parent)
{
	if(parent)
	{
		fun_ptr(parent->data);
		PrO_Traverse(fun_ptr, parent->left);
		PrO_Traverse(fun_ptr, parent->right);
	}
}

//Breadth-First Traversal
template< class T >
void tAVL< T >::BF_Traverse( void(*fun_ptr)(const T& data) )
{
	tQueue< tAVLNode< T >* > BF_Q;
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
		throw EXCEPTION("void tAVL< T >::BF_Traverse( void(*fun_ptr)(const T& data) )^no data^");
	}
}


//Purge – Destroy the tree.
template< class T >
void tAVL< T >::Purge()
{
	delete root;
	root = 0;
}

//Height – Find the height of the tree.
template< class T >
int tAVL< T >::Height()
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
template< class T >
int tAVL< T >::Height(const tAVLNode< T >* top, int current_height)
{
	int left_height(0);
	int right_height(0);
	int total_height(current_height);

	if(top)
	{
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
	}

      return total_height; 
}

template< class T >
tAVL< T >& tAVL< T >::operator=(const tAVL< T >& copyme)
{
	tQueue< tAVLNode< T >* > copy_Q;
	tQueue< tAVLNode< T >* > parent_Q;
	int level_size(0);

	if(copyme.root)
	{
		copy_Q.Enqueue(copyme.root);
		int copy_count(0);
		root = new tAVLNode< T >(*copy_Q.Front());
		parent_Q.Enqueue(root);
		
		while(!copy_Q.isEmpty())
		{
			level_size = copy_Q.Size();
			for(int i = 0; i < level_size; i++)
			{

				if( copy_Q.Front()->left )
				{
					copy_Q.Enqueue(copy_Q.Front()->left);
					parent_Q.Front()->left = new tAVLNode< T >(*copy_Q.Front()->left);
					parent_Q.Enqueue(parent_Q.Front()->left);
				}
				if( copy_Q.Front()->right )
				{
					copy_Q.Enqueue(copy_Q.Front()->right);
					parent_Q.Front()->right = new tAVLNode< T >(*copy_Q.Front()->right);
					parent_Q.Enqueue(parent_Q.Front()->right);
				}

				copy_Q.Dequeue();
				parent_Q.Dequeue();
			}
		}
	}
	
	return *this;
}

//Balances the tree
template< class T >
void tAVL< T >::Balance()
{
	//RRRotate(root);
	root->right->left = root;
	root = root->right;
	root->left->right = 0;

	cout<<BalanceFactor(root)<<"\n"
		<<BalanceFactor(root->right)<<"\n"
		<<BalanceFactor(root->left)<<"\n";
}

template< class T >
int tAVL< T >::BalanceFactor(const tAVLNode< T >* ofMe)
{
	int BFactor(0);

	if(ofMe->left)
	{
		BFactor = Height(ofMe->left);
	}
	if(ofMe->right)
	{
		BFactor = BFactor - Height(ofMe->right);
	}
	return BFactor;
}

template< class T >
void tAVL< T >::LLRotate(tAVLNode< T >* axis_node)
{
}

template< class T >
void tAVL< T >::RRRotate(tAVLNode< T >*& axis_node)
{
	axis_node->right->left = axis_node;
	axis_node = axis_node->right;
	axis_node->left->right = 0;
}

//---------- Ctors and Dtors -------------------
template< class T >
tAVL< T >::tAVL()
			  :root(0)
{
}

template< class T >
tAVL< T >::tAVL(const tAVL< T >& copyme)
{
	*this = copyme;
}

template< class T >
tAVL< T >::~tAVL()
{
	if(root != 0)
	{
		delete root;
	}
	root = 0;
}

#endif