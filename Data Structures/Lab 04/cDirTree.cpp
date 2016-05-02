#include "cDirTree.h"
#include<iostream>
using std::cout;

/**************************************************************
*   Entry:  call to the nodes display function.
*
*    Exit:  The entire tree will be printed to the screen.
*
* Purpose:  To display the data in our tree.
*
***************************************************************/
void cDirTree::Display()
{
	root->Display(0);
}

/**************************************************************
*   Entry:  A valid path.
*
*    Exit:  The tree will be instantiated with folder/file
*			objects.
*
* Purpose:  To instantiate our tree.
*
***************************************************************/
cDirTree::cDirTree(const String& Root_String)
{
	root = new cDTNode(Root_String, "_", true);	
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  default deconstructor
*
***************************************************************/
cDirTree::~cDirTree()
{
	delete root;
}