#include "gene.h"
#include <iostream>

Gene::Gene()
{

	std::cout<<"Constructor hit\n";
	RandObj.init_Randomize();

	vctGenomes.clear();
	for( int i = 0; i < 4; ++i )
	{
		vctGenomes.push_back( new int );
	}

	initGene();
}

Gene::Gene( const Gene& cpyMe )
{
	DeleteGenes();
	
	for( int i = 0; i < 4; ++i )
	{
		vctGenomes.push_back( new int( (*cpyMe)[i] ) );
	}
}

Gene::~Gene()
{
	DeleteGenes();
}

void Gene::initGene()
{
	for( std::vector< int* >::iterator i = vctGenomes.begin(); i != vctGenomes.end(); ++i )
	{
		(*(*i)) = RandObj.Randomize( 0, 1 );
	}
}

Gene::operator const char*()
{
	std::string strReturn;
	strReturn.clear();

	strReturn += iFitness;
	strReturn += " ";
	strReturn += iXVal;
	strReturn += " ";
	for( std::vector< int* >::iterator i = vctGenomes.begin(); i != vctGenomes.end(); ++i )
	{
		strReturn += (*(*i));
		strReturn += " ";
	}

	return strReturn.c_str();
}

int* Gene::operator []( const int& iIndex ) const
{
	int* ptrReturn(0);
	if( iIndex < 4 && iIndex > -1 )
	{
		ptrReturn = vctGenomes[iIndex];
	}
	return ptrReturn;
}

void Gene::DeleteGenes()
{
	if( !vctGenomes.empty() )
	{
		for( std::vector< int* >::iterator i = vctGenomes.begin(); i != vctGenomes.end(); ++i )
		{
			delete (*i);
		}
		vctGenomes.clear();
	}
}