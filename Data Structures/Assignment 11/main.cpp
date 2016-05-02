#include <iostream>
using std::cout;

#include "tAVL.h"
#include "Error.h"

void PrintOut(const int&);

int main()
{
	tAVL< int > yourTree;

	tAVL< int > AVLTree;

	try
	{
		AVLTree.Recursive_Insert(8);
		AVLTree.Recursive_Insert(9);
		AVLTree.Recursive_Insert(10);
		AVLTree.Balance();


		cout<<"----- Pre-AVL functions -----\n";
		yourTree.Iterative_Insert(20);
		yourTree.Iterative_Insert(15);
		yourTree.Iterative_Insert(25);

		yourTree.Recursive_Insert(30);
		yourTree.Recursive_Insert(12);
		yourTree.Recursive_Insert(18);
		yourTree.Recursive_Insert(11);

		cout<<"Copying the tree\n";
		tAVL< int > myTree(yourTree);

		cout<<"\nHeight of our tree is: "<<myTree.Height()<<"\n";

		cout<<"\n\nIn-Order Traversal\n";
		myTree.IO_Traverse(PrintOut);
		cout<<"\nPost-Order Traversal\n";
		myTree.PO_Traverse(PrintOut);
		cout<<"\nPre-Order Traversal\n";
		myTree.PrO_Traverse(PrintOut);
		cout<<"\nBreadth-First Traversal\n";
		myTree.BF_Traverse(PrintOut);

		//case 1
		cout<<"\nDeleting 11...\n";
		myTree.Iterative_Delete(11);
		cout<<"Inserting 11...\n";
		myTree.Iterative_Insert(11);

		//case 2
		cout<<"Deleting 25...\n";
		myTree.Recursive_Delete(25);
		cout<<"Inserting 25...\n";
		myTree.Recursive_Insert(25);

		//case 3
		cout<<"Deleting 12...\n";
		myTree.Iterative_Delete(12);
		cout<<"Inserting 12...\n";
		myTree.Iterative_Insert(12);

		//case 4
		cout<<"Deleting 15...\n";
		myTree.Recursive_Delete(15);
		cout<<"Inserting 15...\n";
		myTree.Recursive_Insert(15);

		cout<<"Operations done\n";
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}

	return 0;
}

void PrintOut(const int& printme)
{
	cout<<printme<<"\n";
}