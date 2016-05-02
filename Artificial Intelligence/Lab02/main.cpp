/*************************************************************************** 
Alberto Martinez 

02/23/2006 

CST426 - AI - Lab 02
main.cpp
***************************************************************************/ 

#include<iostream>
#include<list>

void Moisture_Fuzzify( const float&, float&, float& );
void Gluten_Fuzzify( const float&, float&, float&, float& );
std::list< float > Temperature_Ruleset( const float&, const float&, const float&, const float&, const float& );
std::list< float > Time_Ruleset( const float&, const float&, const float&, const float&, const float& );
float WATemperature( std::list< float >& );
float WATime( std::list< float >& );
float Min( const float&, const float& );
float Max( const float&, const float&, const float& );

int main()
{
	int moisture_percentage(0);
	int gluten_percentage(0);

	//input moisture_percentage
	std::cout<<"Please input the percentage of moisture in the rice: ";
	std::cin>>moisture_percentage;

	//calculate moisture_content
	float moisture_content( (moisture_percentage - 5.0f) / 15.0f );

	//input gluten_percentage
	std::cout<<"\nPlease input the percentage of gluten in the rice: ";
	std::cin>>gluten_percentage;

	//calculate gluten_content
	float gluten_content( (gluten_percentage - 1.0f) / 29.0f );

	//fuzzy logic

		//fuzzify moisture_content into moisture_old and moisture_new
		float moisture_old(0);
		float moisture_new(0);
		Moisture_Fuzzify( moisture_content, moisture_old, moisture_new );

		//fuzzify gluten_content into gluten_long_grain, gluten_medium_grain, gluten_short_grain
		float gluten_long_grain(0);
		float gluten_medium_grain(0);
		float gluten_short_grain(0);
		Gluten_Fuzzify( gluten_content, gluten_long_grain, gluten_medium_grain, gluten_short_grain );

		//Fire Rulesets
		std::list< float > lstTemp;
		std::list< float > lstTime;
		lstTemp = Temperature_Ruleset( moisture_old, moisture_new, gluten_short_grain, gluten_medium_grain, gluten_long_grain );
		lstTime = Time_Ruleset( moisture_old, moisture_new, gluten_short_grain, gluten_medium_grain, gluten_long_grain );

	//output cooking_time//output cooking_temperature
	std::cout<<"\nCook the rice for "<< ( 100 * WATime( lstTime ) ) + 20 <<" minutes at "<<( 20 * WATemperature( lstTemp ) ) + 80<<" degrees.\n";
}

void Moisture_Fuzzify( const float& moisture_content, float& moisture_old, float& moisture_new )
{
	if( 0.25 < moisture_content && moisture_content < 0.75f )
	{
		//calc fuzzy value of moisture_old
<<<<<<< .mine
		moisture_new = ( moisture_content - 0.25f ) / 0.5f;
		moisture_old = 1 - moisture_new;
=======
		moisture_old = 1 / ( 0.75 - moisture_content );
		moisture_new = 1 - moisture_old;
>>>>>>> .r72
	}
	else if( moisture_content <= 0.25f )
	{
		moisture_old = 1.0f;
		moisture_new = 0.0f;
	}
	else
	{
		moisture_new = 1.0f;
		moisture_old = 0.0f;
	}
}

void Gluten_Fuzzify( const float& gluten_content, float& gluten_long_grain, float& gluten_medium_grain, float& gluten_short_grain )
{
	if( 0.25f < gluten_content && gluten_content < 0.75f )
	{
		if( gluten_content < 0.75f && gluten_content > 0.5f )
		{
			gluten_short_grain = (gluten_content - 0.5f) / 0.25f;
			gluten_medium_grain = (0.75f - gluten_content) / 0.25f;
			gluten_long_grain = 1.0f - gluten_short_grain - gluten_medium_grain;
		}
		else if( gluten_content > 0.25f && gluten_content < 0.5f )
		{
			gluten_long_grain = (gluten_content - 0.5f) / 0.25f;
			gluten_medium_grain = (0.75f - gluten_content) / 0.25f;
			gluten_short_grain = 1.0f - gluten_long_grain - gluten_medium_grain;
		}
		else
		{
			gluten_medium_grain = 1.0f;
			gluten_short_grain = 0.0f;
			gluten_long_grain = 0.0f;
		}
	}
	else if( gluten_content <= 0.25f )
	{
		gluten_long_grain = 1.0f;
		gluten_medium_grain = 0.0f;
		gluten_short_grain = 0.0f;
	}
	else
	{
		gluten_long_grain = 0.0f;
		gluten_medium_grain = 0.0f;
		gluten_short_grain = 1.0f;
	}
}

std::list< float > Temperature_Ruleset( const float& moisture_old, const float& moisture_new, const float& gluten_short_grain, const float& gluten_medium_grain, const float& gluten_long_grain )
{
	std::list< float > lstReturn;
	//rule 1
	if( gluten_long_grain && moisture_old )
	{
		lstReturn.push_back( Min( gluten_long_grain, moisture_old ) );
	}
	//rule 2
	if( gluten_long_grain && moisture_new )
	{
		lstReturn.push_back( Min( gluten_long_grain, moisture_new ) );
	}
	//rule 3
	if( gluten_medium_grain && moisture_old )
	{
		lstReturn.push_back( Min( gluten_medium_grain, moisture_old ) );
	}
	//rule 4
	if( gluten_medium_grain && moisture_new )
	{
		lstReturn.push_back( Min( gluten_medium_grain, moisture_new ) );
	}
	//rule 5
	if( gluten_short_grain || moisture_old || moisture_new )
	{
		lstReturn.push_back( Max( gluten_short_grain, moisture_old, moisture_new ) );
	}

	return lstReturn;
}

std::list< float > Time_Ruleset( const float& moisture_old, const float& moisture_new, const float& gluten_short_grain, const float& gluten_medium_grain, const float& gluten_long_grain )
{
	std::list< float > lstReturn;
	//rule 1
	if( gluten_long_grain || moisture_old || moisture_new )
	{
		lstReturn.push_back( Max( gluten_long_grain, moisture_old, moisture_new ) );
	}
	//rule 2
	if( gluten_medium_grain && moisture_old )
	{
		lstReturn.push_back( Min( gluten_medium_grain, moisture_old ) );
	}
	//rule 3
	if( gluten_medium_grain && moisture_new )
	{
		lstReturn.push_back( Min( gluten_medium_grain, moisture_new ) );
	}
	if( gluten_short_grain || moisture_old || moisture_new )
	{
		lstReturn.push_back( Max( gluten_short_grain, moisture_old, moisture_new ) );
	}
	return lstReturn;
}

float WATemperature( std::list< float >& lstTemp )
{
	float numerator(0);
	float denominator(0);
	for( std::list< float >::iterator i = lstTemp.begin(); i != lstTemp.end(); ++i )
	{
		if( (*i) < 0.5f )
		{
			numerator += (*i) * 0.5f;
		}
		else
		{
			numerator += (*i) * 0.75f;
		}
		denominator += (*i);
	}
	return (numerator / denominator);
}

float WATime( std::list< float >& lstTime )
{
	float numerator(0);
	float denominator(0);
	for( std::list< float >::iterator i = lstTime.begin(); i != lstTime.end(); ++i )
	{
		//time short
		if( (*i) < 0.25f )
		{
			numerator += (*i) * 0.25f;
		}
		else if( (*i) >= 0.25f && (*i) < 0.75f )
		{
			numerator += (*i) * 0.5f;
		}
		else
		{
			numerator += (*i) * 0.75f;
		}
		denominator += (*i);
	}
	return (numerator / denominator);
}

float Min( const float& a, const float& b )
{
	float fReturn(0);
	if( b < a )
	{
		fReturn = b;
	}
	else
	{
		fReturn = a;
	}
	return fReturn;
}

float Max( const float& a, const float& b, const float& c )
{
	float fReturn(0);
	if( b > a && b > c )
	{
		fReturn = b;
	}
	else if( a > b && a > c )
	{
		fReturn = a;
	}
	else
	{
		fReturn = c;
	}
	return fReturn;
}