/*************************************************************************** 
Alberto Martinez 

10/18/2005 

statetree.h


***************************************************************************/


#ifndef STATETREE_H
#define STATETREE_H

#include <string>
#include <vector>
#include "statenode.h"

class StateTree
{
	public:
		StateTree( const std::string& );
		~StateTree();
		bool CheckInput( const std::string& );

	private:
		bool CheckAlpha( char );
		int ptr_Head;
		std::vector< char > vct_alphabet;
		std::vector< StateNode* > vct_States;

};

#endif