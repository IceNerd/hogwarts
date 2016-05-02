/*************************************************************************** 
Alberto Martinez 

10/18/2005 

statetree.cpp


***************************************************************************/


#include <fstream>
#include <vector>
#include "statetree.h"

//***** Public - Constructor ***************************************
StateTree::StateTree( const std::string& FileInput )
{
	char cFromFile(0);
	char cToState(0);
	int test(0);

	std::ifstream ptr_file( FileInput.c_str() );

	if( ptr_file.is_open() )
	{
		//clear alphabet list
		this->vct_alphabet.clear();

		//clear states
		for( std::vector< StateNode* >::iterator iter_States = this->vct_States.begin(); iter_States != vct_States.end(); ++iter_States )
		{
			delete (*iter_States);
		}
		this->vct_States.clear();

		while( cFromFile != 10 )
		{
			//Get Alphabet
			ptr_file.get( cFromFile );
			//Load each character into alphabet list
			this->vct_alphabet.push_back( cFromFile );
		}
		//remove last one because it is not in the alphabet
		this->vct_alphabet.pop_back();
		
		//Get State Transitions (create states)
		while( !ptr_file.eof() )
		{
			ptr_file.get( cFromFile );
			switch( cFromFile )
			{
				case 84://New State with Transition States
					//std::cout<<"Creating new state\n";
					this->vct_States.push_back( new StateNode() );
					ptr_file.get( cFromFile );
					while( cFromFile != 10 )
					{
						ptr_file.get( cToState );
						//On Which Alphabet occurance transition to
						this->vct_States.back()->AddEdge( cFromFile, int(cToState) - 48 );
						//std::cout<<"Transition State Added\n";
						ptr_file.get( cFromFile );
					}
				break;

				case 83://Set Starting State
					//std::cout<<"Setting start state\n";
					ptr_file.get( cFromFile );
					this->ptr_Head = int(cFromFile) - 48;
					//std::cout<<"State "<<int(cFromFile) - 48<<" set as the starting state\n";
				break;

				case 70://Set Accepting States
					//std::cout<<"Setting accepting states\n";
					ptr_file.get( cFromFile );
					while( ( cFromFile != 10 ) && !(ptr_file.eof()) )
					{
						this->vct_States[cFromFile - 48]->ChangeAcceptingState( true );
						//std::cout<<"State "<<int(cFromFile) - 48<<" set as an accepting state\n";
						ptr_file.get( cFromFile );
					}
				break;
			}
		}

		ptr_file.close();
	}
	else
	{
		//std::cout<<"File IO Error: File not Open.  Machine not defined!\n";
	}
}

//***** Public - Destructor ****************************************
StateTree::~StateTree()
{
		//clear alphabet list
		this->vct_alphabet.clear();

		//clear states
		for( std::vector< StateNode* >::iterator iter_States = this->vct_States.begin(); iter_States != vct_States.end(); ++iter_States )
		{
			delete (*iter_States);
		}
		this->vct_States.clear();
}

//***** Public *****************************************************

//********** CheckInput
bool StateTree::CheckInput( const std::string& str_Input )
{
	bool bInput( true );
	int ptr_Traveler( this->ptr_Head );
	for( int iCursor = 0; ( iCursor != str_Input.length() ) && ( bInput == true ); ++iCursor )
	{
		if( CheckAlpha( str_Input[iCursor] ) )
		{
			ptr_Traveler = this->vct_States[ptr_Traveler]->Traverse( str_Input[iCursor] );
			if( ptr_Traveler == -1 )
			{
				//std::cout<<str_Input[iCursor]<<" error\n";
				bInput = false;
			}
		}
		else
		{
			//std::cout<<str_Input[iCursor]<<" not in the alphabet\n";
			bInput = false;
		}
	}
	if( ptr_Traveler > -1 )
	{
		bInput = this->vct_States[ptr_Traveler]->AcceptingState();
	}
	return bInput;
}

//***** Private ****************************************************

//********** CheckAlpha
bool StateTree::CheckAlpha( char cCheck )
{
	bool bValid( false );

	for( std::vector< char >::iterator iter_Alpha = this->vct_alphabet.begin(); ( iter_Alpha != vct_alphabet.end() ) && ( bValid == false ); ++iter_Alpha )
	{
		if( (*iter_Alpha) == cCheck )
		{
			bValid = true;
		}
	}
	return bValid;
}