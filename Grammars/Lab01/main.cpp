/*************************************************************************** 
Alberto Martinez 

10/18/2005 

main.cpp


***************************************************************************/


#include< iostream >
#include "statetree.h"

int main()
{
	char str_Input[100]( "blah" );

	std::cout<<"CST229 - Lab 01 - Regular Language Recognizer\n";

	//Retrieve information from Input File about machine M
	std::cout<<"FileName: ";
	std::cin>>str_Input;
	StateTree myTree( str_Input );
	std::cout<<"Machine Created\n\n";

	//Retrieve input strings and check if input is valid
	while( strcmp(str_Input, "exit") != 0 )
	{
		std::cout<<"input: ";
		std::cin>>str_Input;
		if( myTree.CheckInput( str_Input ) )
		{
			std::cout<<"+++Valid Input+++\n\n";
		}
		else
		{
			std::cout<<"---Invalid Input---\n\n";
		}
	}
}