#include <iostream>
#include <vector>

#include "random.h"

void SortByFitness( std::vector< std::vector< int > >& );
int SumOfGeneVals( std::vector< std::vector< int > >&, const int& );
void PrintMatrix( std::vector< std::vector< int > >& );

int main()
{
	//(1) First you will initialize the values of the needed variables:
	const int num_genes = 6;
	const int num_generations = 50;
	const int mutation = 0;
	std::vector< std::vector< int > > gene_matrix( num_genes, std::vector< int >(6, 0) ) ;
	std::vector< std::vector< int > > temp( num_genes, std::vector< int >(6, 0) );
	std::vector< int > f_avg( num_generations, 0);
	std::vector< int > g_vec( num_generations, 0);
	Random RandObj;

	//(2) Next you will use a random number generator to create the initial gene population:
	for( int i = 0; i < num_genes; ++i )
	{
		for( int j = 2; j < 6; ++j )
		{
			gene_matrix[i][j] = RandObj.Randomize( 0, 1 );
		}
	}

	//(3) Now you will start iterating on the generations:
	for( int generation_counter = 0; generation_counter < num_generations; ++generation_counter )
	{

	//(4) You will next calculate the x value and fitness value for each gene:
		for( int i = 0; i < num_genes; ++i )
		{
			gene_matrix[i][1] = 8*gene_matrix[i][2]+4*gene_matrix[i][3]+2*gene_matrix[i][4]+1*gene_matrix[i][5];
			gene_matrix[i][0] = (15*gene_matrix[i][1]) - (gene_matrix[i][1] * gene_matrix[i][1]);
		}

	//(5) As a simplified form of roulette wheel selection you will order
	//    the genome array by the fitness value from least fit to most fit.
	//    You will then replace the two most significant bits of the two
	//    middle fitness genes with the corresponding bits of the fittest
	//    genes:
		SortByFitness( gene_matrix );
		for( int i = 2; i < 4; ++i )
		{
			gene_matrix[num_genes - 4][i] = gene_matrix[num_genes - 1][i];
			gene_matrix[num_genes - 5][i] = gene_matrix[num_genes - 2][i];
		}

	//(6) You will now scan the genes and invert a random bit using the
	//    mutation rate.
		for( std::vector< std::vector< int > >::iterator i = gene_matrix.begin(); i != gene_matrix.end(); ++i )
		{
			for( int j = 2; j < 6; ++j )
			{
				if( RandObj.Randomize( 0, 100 ) < mutation )
				{
					if( (*i)[j] == 0 )
					{
						(*i)[j] = 1;
					}
					else
					{
						(*i)[j] = 0;
					}
				}
			}
		}

	//(7) Finally you wil update teh needed data to plot the average value
	//    of all six genes versus the generation number:
		f_avg[generation_counter] = SumOfGeneVals( gene_matrix, num_genes ) / num_genes;
		g_vec[generation_counter] = generation_counter;
	}

	for( int i = 0; i < num_generations; ++i )
	{
		std::cout<<f_avg[i]<<"\n";
	}
}

void SortByFitness( std::vector< std::vector< int > >& sortMe )
{
	std::vector< int > vctSwap;
	vctSwap.clear();

	//basic bubble sort
	for( std::vector< std::vector< int > >::iterator i = sortMe.begin(); i != sortMe.end(); ++i )
	{
		for( std::vector< std::vector< int > >::iterator j = i; j!= sortMe.end(); ++j )
		{
			if( (*i)[0] > (*j)[0] )
			{
				vctSwap = (*i);
				(*i).clear();
				(*i) = (*j);
				(*j).clear();
				(*j) = vctSwap;
				vctSwap.clear();
			}
		}
	}
}

int SumOfGeneVals( std::vector< std::vector< int > >& gene_matrix, const int& num_genes )
{
	int sum(0);

	for( int i = 0; i < num_genes; ++i )
	{
		sum += gene_matrix[i][0];
	}

	return sum;
}

//not used in final implementation
void PrintMatrix( std::vector< std::vector< int > >& PrintMe )
{
	for( std::vector< std::vector< int > >::iterator i = PrintMe.begin(); i != PrintMe.end(); ++i )
	{
		for( std::vector< int >::iterator j = (*i).begin(); j!= (*i).end(); ++j )
		{
			std::cout.width( 3 );
			std::cout<<(*j);
		}
		std::cout<<"\n";
	}
}