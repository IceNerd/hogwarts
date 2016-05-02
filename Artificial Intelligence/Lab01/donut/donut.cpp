#include<string>
#include "donut.h"

Donut::Donut( char* initDonutDesc, int initType, int initDough, int initFilling, int initFruit, int initCoating, int initDecoration, int initSpice, int initShape )
:Type( &donType ),
CakeDough( &donCakeDough ),
Filling( &donFilling ),
Fruit( &donFruit ),
Coating( &donCoating ),
Decoration( &donDecoration ),
Spice( &donSpice ),
Shape( &donShape ),
donType( initType ),
donCakeDough( initDough ),
donFilling( initFilling ),
donFruit( initFruit ),
donCoating( initCoating ),
donDecoration( initDecoration ),
donSpice( initSpice ),
donShape( initShape ),
strDonutDesc( initDonutDesc )
{
}

Donut::~Donut()
{
}

bool Donut::operator ==( Donut& cmpDonut )
{
	return( this->donType == cmpDonut.Type &&
			this->donCakeDough == cmpDonut.CakeDough &&
			this->donFilling == cmpDonut.Filling &&
			this->donFruit == cmpDonut.Fruit &&
			this->donCoating == cmpDonut.Coating &&
			this->donDecoration == cmpDonut.Decoration &&
			this->donSpice == cmpDonut.Spice &&
			this->donShape == cmpDonut.Shape );
}

Donut::operator char*()
{
	return this->strDonutDesc;
}