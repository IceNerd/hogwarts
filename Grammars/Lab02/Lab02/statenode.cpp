/*************************************************************************** 
Alberto Martinez 

10/18/2005 

statenode.cpp


***************************************************************************/


#include "statenode.h"

//***** Public - Constructor ***************************************
StateNode::StateNode()
:bAccept(false), defTrans(-1)
{
}

//***** Public - Destructor ****************************************
StateNode::~StateNode()
{
}

//***** Public *****************************************************

//********** AddEdge
void StateNode::AddEdge( char cVal, int iState )
{
	//std::cout<<"Added Edge: "<<cVal<<" "<<iState<<"\n";
	if( cVal == '*' )
	{
		this->defTrans = iState;
	}
	else
	{
		std::pair<char, int> toAdd( cVal, iState );
		this->mapTransitions.insert( toAdd );
	}
}

//********** ChangeAcceptingState
void StateNode::ChangeAcceptingState( bool bAcceptable )
{
	this->bAccept = bAcceptable;
}

//********** AcceptingState
bool StateNode::AcceptingState()
{
	return this->bAccept;
}

//********** Traverse
int StateNode::Traverse( char cVal )
{
	int iReturn( -1 );

	std::map<char, int>::const_iterator iter_i;

	iter_i = this->mapTransitions.find( cVal );
	if( iter_i != this->mapTransitions.end() )
	{
		iReturn = iter_i->second;
	}
	else
	{
		iReturn = this->defTrans;
	}
	return iReturn;
}