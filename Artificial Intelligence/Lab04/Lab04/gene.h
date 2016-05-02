#ifndef GENE_H
#define GENE_H

#include <vector>
#include <string>

#include "random.h"

class Gene
{
public:
	Gene();
	Gene( const Gene& );
	~Gene();
	void initGene();
	operator const char*();
	int* operator []( const int& ) const;

private:
	void DeleteGenes();

	int iFitness;
	int iXVal;
	std::vector< int* > vctGenomes;
	Random RandObj;

};

#endif