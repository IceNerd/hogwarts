#include <iostream>
#include <vector>
#include <cmath>

#include "lab03def.h"

int main()
{
	int iEpoch(0);
	float ALPHA(0.9f);
	float BETA(0.2f);
	float GAMMA(0.1f);
	int X1(0), X2(0), X3(0);
	int CaseCount(0);
	float Error7(0), Error8(0);
	float DError(0), DError_old(0);
	float Y7Desired( 1.0f );
	float Y8Desired( 0.0f );
	float SumSquared_new(1.0f), SumSquared_old(0), SumSquared_older(0);
	
	std::vector< float > W_New( 15, 0.0f );
	std::vector< float > W_Old( 15, 0.5f );
	std::vector< float > W_Older( 15, 0.0f );
	std::vector< float > Theta_New( 5, 1.0f );
	std::vector< float > Theta_Old( 5, 1.0f );
	std::vector< float > Theta_Older( 5, 1.0f );
	std::vector< float > YOutput( 5, 0.0f );

	std::vector< float > Y7Final( 8, 0.0f );
	std::vector< float > Y8Final( 8, 0.0f );

	do
	{
		CaseCount = 0;
		for( X1 = 0; X1 < 2; ++X1 )
		{
			for( X2 = 0; X2 < 2; ++X2 )
			{
				for( X3 = 0; X3 < 2; ++X3 )
				{
					//Part (B)
					YOutput[Y4] = 1 / ( 1 + exp( -( X1 * W_Old[W14] + X2 * W_Old[W24] + X3 * W_Old[W34] - Theta_Old[A4] ) ) );
					YOutput[Y5] = 1 / ( 1 + exp( -( X1 * W_Old[W15] + X2 * W_Old[W25] + X3 * W_Old[W35] - Theta_Old[A5] ) ) );
					YOutput[Y6] = 1 / ( 1 + exp( -( X1 * W_Old[W16] + X2 * W_Old[W26] + X3 * W_Old[W36] - Theta_Old[A6] ) ) );
					YOutput[Y7] = 1 / ( 1 + exp( -( YOutput[Y4] * W_Old[W47] + YOutput[Y5] * W_Old[W57] + YOutput[Y6] * W_Old[W67] - Theta_Old[A7] ) ) );
					YOutput[Y8] = 1 / ( 1 + exp( -( YOutput[Y4] * W_Old[W48] + YOutput[Y5] * W_Old[W58] + YOutput[Y6] * W_Old[W68] - Theta_Old[A8] ) ) );

					//Part (C)
					if( CaseCount < 4 )
					{
						Y7Desired = 1.0f;
						Y8Desired = 0.0f;
					}
					else
					{
						Y7Desired = 0.0f;
						Y8Desired = 1.0f;
					}
					Error7 = -YOutput[Y7] * (1 - YOutput[Y7]) * ( YOutput[Y7] - Y7Desired );
					Error8 = -YOutput[Y8] * (1 - YOutput[Y8]) * ( YOutput[Y8] - Y8Desired );

					W_New[W47] = W_Old[W47] + ALPHA * YOutput[Y4] * Error7;
					W_New[W48] = W_Old[W48] + ALPHA * YOutput[Y4] * Error8;
					W_New[W57] = W_Old[W57] + ALPHA * YOutput[Y5] * Error7;
					W_New[W58] = W_Old[W58] + ALPHA * YOutput[Y5] * Error8;
					W_New[W67] = W_Old[W67] + ALPHA * YOutput[Y6] * Error7;
					W_New[W68] = W_Old[W68] + ALPHA * YOutput[Y6] * Error8;
					Theta_New[A7] = Theta_Old[A7] + ALPHA * (-1) * Error7;
					Theta_New[A8] = Theta_Old[A8] + ALPHA * (-1) * Error8;

					W_New[W14] = W_Old[W14] + ALPHA * X1 * YOutput[Y4] * (1 - YOutput[Y4]) * (W_Old[W47] * Error7 + W_Old[W48] * Error8);
					W_New[W15] = W_Old[W15] + ALPHA * X1 * YOutput[Y5] * (1 - YOutput[Y5]) * (W_Old[W57] * Error7 + W_Old[W58] * Error8);
					W_New[W16] = W_Old[W16] + ALPHA * X1 * YOutput[Y6] * (1 - YOutput[Y6]) * (W_Old[W67] * Error7 + W_Old[W68] * Error8);
					W_New[W24] = W_Old[W24] + ALPHA * X2 * YOutput[Y4] * (1 - YOutput[Y4]) * (W_Old[W47] * Error7 + W_Old[W48] * Error8);
					W_New[W25] = W_Old[W25] + ALPHA * X2 * YOutput[Y5] * (1 - YOutput[Y5]) * (W_Old[W57] * Error7 + W_Old[W58] * Error8);
					W_New[W26] = W_Old[W26] + ALPHA * X2 * YOutput[Y6] * (1 - YOutput[Y6]) * (W_Old[W67] * Error7 + W_Old[W68] * Error8);
					W_New[W34] = W_Old[W34] + ALPHA * X3 * YOutput[Y4] * (1 - YOutput[Y4]) * (W_Old[W47] * Error7 + W_Old[W48] * Error8);
					W_New[W35] = W_Old[W35] + ALPHA * X3 * YOutput[Y5] * (1 - YOutput[Y5]) * (W_Old[W57] * Error7 + W_Old[W58] * Error8);
					W_New[W36] = W_Old[W36] + ALPHA * X3 * YOutput[Y6] * (1 - YOutput[Y6]) * (W_Old[W67] * Error7 + W_Old[W68] * Error8);
					Theta_New[A4] = Theta_Old[A4] + ALPHA * (-1) * YOutput[Y4] * (1 - YOutput[Y4]) * (W_Old[W47] * Error7 + W_Old[W48] * Error8 );
					Theta_New[A5] = Theta_Old[A5] + ALPHA * (-1) * YOutput[Y5] * (1 - YOutput[Y5]) * (W_Old[W57] * Error7 + W_Old[W58] * Error8 );
					Theta_New[A6] = Theta_Old[A6] + ALPHA * (-1) * YOutput[Y6] * (1 - YOutput[Y6]) * (W_Old[W67] * Error7 + W_Old[W68] * Error8 );

					//Refinement (A)
					W_New[W47] = W_New[W47] + BETA * (W_Old[W47] - W_Older[W47]);
					W_New[W48] = W_New[W48] + BETA * (W_Old[W48] - W_Older[W48]);
					W_New[W57] = W_New[W57] + BETA * (W_Old[W57] - W_Older[W57]);
					W_New[W58] = W_New[W58] + BETA * (W_Old[W58] - W_Older[W58]);
					W_New[W67] = W_New[W67] + BETA * (W_Old[W67] - W_Older[W67]);
					W_New[W68] = W_New[W68] + BETA * (W_Old[W68] - W_Older[W68]);
					W_New[W14] = W_New[W14] + BETA * (W_Old[W14] - W_Older[W14]);
					W_New[W15] = W_New[W15] + BETA * (W_Old[W15] - W_Older[W15]);
					W_New[W16] = W_New[W16] + BETA * (W_Old[W16] - W_Older[W16]);
					W_New[W24] = W_New[W24] + BETA * (W_Old[W24] - W_Older[W24]);
					W_New[W25] = W_New[W25] + BETA * (W_Old[W25] - W_Older[W25]);
					W_New[W26] = W_New[W26] + BETA * (W_Old[W26] - W_Older[W26]);
					W_New[W34] = W_New[W34] + BETA * (W_Old[W34] - W_Older[W34]);
					W_New[W35] = W_New[W35] + BETA * (W_Old[W35] - W_Older[W35]);
					W_New[W36] = W_New[W36] + BETA * (W_Old[W36] - W_Older[W36]);
					Theta_New[A7] = Theta_New[A7] + BETA * (Theta_Old[A7] - Theta_Older[A7]);
					Theta_New[A6] = Theta_New[A6] + BETA * (Theta_Old[A6] - Theta_Older[A6]);
					Theta_New[A5] = Theta_New[A5] + BETA * (Theta_Old[A5] - Theta_Older[A5]);
					Theta_New[A4] = Theta_New[A4] + BETA * (Theta_Old[A4] - Theta_Older[A4]);
					//End Refinement (A)

					SumSquared_older = SumSquared_old;
					SumSquared_old = SumSquared_new;
					SumSquared_new = sqrt( Error7 * Error7 + Error8 * Error8 );

					W_Older = W_Old;
					Theta_Older = Theta_Old;
					W_Old = W_New;
					Theta_Old = Theta_New;
	
					Y7Final[CaseCount] = YOutput[Y7];
					Y8Final[CaseCount] = YOutput[Y8];

					CaseCount++;
				}
			}
		}

		DError = SumSquared_new - SumSquared_old;
		DError_old = SumSquared_old - SumSquared_older;

		//Refinement(B)
		if( (DError * DError_old) > 0 )
		{
			ALPHA = (1 + GAMMA) * ALPHA;
		}

		if( (DError * DError_old) < 0 )
		{
			ALPHA = (1 - GAMMA) * ALPHA;
		}

		if( ALPHA > 1 )
		{
			ALPHA = 1;
		}
		//End Refinement (B)

		//For printing SumSquared
		//std::cout<<SumSquared_new<<"\n";

		//For Print DError
		//std::cout<<DError<<"\n";
		iEpoch++;
	}
	while( SumSquared_new > ERROR_FINAL );

	//For Printing Y7 and Y8 Final values
		//for( std::vector< float >::iterator i = Y7Final.begin(); i != Y7Final.end(); i++ )
		//{
		//	std::cout<<(*i)<<"\n";
		//}
		//std::cout<<"\n";
		//for( std::vector< float >::iterator i = Y8Final.begin(); i != Y8Final.end(); i++ )
		//{
		//	std::cout<<(*i)<<"\n";
		//}

	std::cout<<iEpoch<<" epochs\n";

	return 0;
}