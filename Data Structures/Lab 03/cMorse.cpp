#include "cMorse.h"
#include "String.h"
#include "Error.h"
#include "Stack.h"

/**************************************************************
*   Entry:  Data must have a value to it
*
*    Exit:  a Character will be returned.
*
* Purpose:  To decode Morse Code into a single character
*
***************************************************************/
char cMorse::Decode(const String& Data)
{
	tTreeNode< char >* cursor(CodeTree.getRoot());
	if(Data == "----")
	{
		return ' ';
	}
	else
	{
		for(int i = 0; (Data[i] == '-') || (Data[i] == '.'); i++)
		{
			if(Data[i] == '.')
			{
				cursor = cursor->getleft();
			}
			else if(Data[i] == '-')
			{
				cursor = cursor->getright();
			}
		}
		return cursor->getData();
	}
}

/**************************************************************
*   Entry:  Data must have a valid value
*
*    Exit:  A string will be returned that represents the
*			given character in morse code.
*
* Purpose:  To encode a character to morse code.
*
***************************************************************/
String cMorse::Encode(const char& Data)
{
	if(Data != ' ')
	{
		tTreeNode< char >* cursor(AlphaList[Data - 65]);
		tStack< char > CodeStack;
		String theCode;
		while( cursor != CodeTree.getRoot() )
		{
			if(cursor->getparent()->getright() == cursor)
			{
				CodeStack.Push('-');
			}
			else if(cursor->getparent()->getleft() == cursor)
			{
				CodeStack.Push('.');
			}
			cursor = cursor->getparent();
		}

		while( !(CodeStack.isEmpty()))
		{
			theCode += CodeStack.Peek();
			CodeStack.Pop();
		}

		return theCode;
	}
	else
	{
		return "----";
	}
}

/**************************************************************
*   Entry:  char* must me a file that holds morse code.
*
*    Exit:  The file will be closed and the codetree will be full
*
* Purpose:  To instantiate the class and the code tree in the
*			class.
*
***************************************************************/
cMorse::cMorse(const char* FileName)
{
	ifstream infile;

	infile.open(FileName);
	if(infile.is_open())
	{
		tLList< String > FileArray;
		while(!infile.eof())
		{
			String fromFile;
			infile>>fromFile;
			FileArray.Append(fromFile);
		}
		infile.close();

		//Make Tree and AlphaArray
		tTreeNode< char >* iter;
		for(int i = 0; i < 26; i++)
		{
			iter = CodeTree.getRoot();
			for(int j = 1; FileArray[i][j] != '0'; j++)
			{
				if(FileArray[i][j] == '.')
				{
					if(!(iter->getleft()))
					{
						iter->newleft(iter, '0');
					}
					iter = iter->getleft();
				}
				else if(FileArray[i][j] == '-')
				{
					if(!(iter->getright()))
					{
						iter->newright(iter, '0');
					}
					iter = iter->getright();
				}
			}
			iter->setData(FileArray[i][0]);
			AlphaList.Append(iter);
		}
		//End Make Tree and AlphaArray
	}
	else
	{
		throw EXCEPTION("cMorse< T >::cMorse(const String& FileName)^Open File Error^\n");
	}
}

/**************************************************************
*   Entry:  <none>
*
*    Exit:  cMorse will be destroyed
*
* Purpose:  to destroy cMorse and all private data.
*
***************************************************************/
cMorse::~cMorse()
{
}