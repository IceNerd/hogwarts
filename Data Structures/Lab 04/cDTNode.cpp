#include "cDTNode.h"
#include<windows.h>
#include<direct.h>
#include<io.h>

#include<iostream>
using std::cout;

/**************************************************************
*   Entry: The directory tree must be instantiated.
*
*    Exit: The contents of the directory tree will be printed
*			to the screen
*
* Purpose: To show the contents of our tree.
*
***************************************************************/
void cDTNode::Display(const int& Depth)
{
	for(int j = 0; j < Depth; j++)
	{
		cout<<"   ";
	}
	if(m_isdir)
	{
		cout<<"\\";
	}
	cout<<m_name<<"\n";

	if(m_isdir)
	{
		if(!m_children.isEmpty())
		{
			for(int i = 0; m_children[i] != m_children.Last(); i++)
			{
				m_children[i]->Display(Depth + 1);
			}
		}
	}
}

/**************************************************************
*   Entry:  For a folder, the path is required.
*
*    Exit:  The tree will be loaded
*
* Purpose:  To instantiate the tree with nodes that represent
*			either a file or folder.  When a node is a folder,
*			the constructor becomes recursive.
*
***************************************************************/
cDTNode::cDTNode(const String& Path, const String& the_name, const bool& isaDir)
		:m_name(the_name), m_isdir(isaDir)
{
	if(isaDir)
	{
		intptr_t hndl;
		_finddata_t* scout;
		scout = new _finddata_t;

		if(_chdir(Path) != -1)
		{
			hndl = _findfirst("*", scout);
			while( _findnext(hndl, scout) != -1 )
			{
				//folder
				if( (scout->attrib & FILE_ATTRIBUTE_DIRECTORY) && ( strcmp(scout->name, ".") ) && ( strcmp(scout->name, "..") ) )
				{
					String newPath(Path);
					newPath += "\\";
					newPath += scout->name;
					
					m_children.Append(new cDTNode(newPath, scout->name, true) );
				}
				//file
				else if( ( strcmp(scout->name, ".") ) && ( strcmp(scout->name, "..") ) )
				{
					m_children.Append(new cDTNode("", scout->name, false));
				}
			}
		}
		else
		{
			throw EXCEPTION("cDTNode::cDTNode(const String& Path, const String& the_name, const bool& isaDir)^Could not open directory^\n");
		}

		delete scout;
		scout = 0;
	}
}

/**************************************************************
*   Entry:  instantiated tree
*
*    Exit:  memory is recovered
*
* Purpose:  to destroy our tree.
*
***************************************************************/
cDTNode::~cDTNode()
{
	m_children.Purge();
}