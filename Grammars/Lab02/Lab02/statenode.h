/*************************************************************************** 
Alberto Martinez 

10/18/2005 

statenode.h


***************************************************************************/

#ifndef STATENODE_H
#define STATENODE_H

#include <map>

class StateNode
{
	public:
		StateNode();
		~StateNode();
		void AddEdge( char, int );
		void ChangeAcceptingState( bool );
		bool AcceptingState();
		int Traverse( char );

	private:
		bool bAccept;
		int defTrans;
		std::map<char, int> mapTransitions;
};

#endif