#include <conio.h>
#include <iostream>
#include <vector>
#include "donut.h"

int main()
{
	bool bEndProg(false);
	int iInput(0);
	Donut mySnack( "My donut" );
	std::vector< Donut* > KrispyKreme;
	KrispyKreme.push_back( new Donut( "Original Glazed" ) );
	KrispyKreme.push_back( new Donut( "Maple Iced",								type_yeast,		cake_dough_none,		filling_none,	fruit_none,			coating_maple,		decoration_none,	spice_none,		shape_torus ) );
	KrispyKreme.push_back( new Donut( "Glazed Cinnamon",						type_yeast,		cake_dough_none,		filling_none,	fruit_none,			coating_glaze,		decoration_none,	spice_cinnamon,	shape_torus ) );
	KrispyKreme.push_back( new Donut( "Glazed Cruller",							type_yeast,		cake_dough_none,		filling_none,	fruit_none,			coating_glaze,		decoration_none,	spice_none,		shape_cruller ) );
	KrispyKreme.push_back( new Donut( "Glazed Blueberry Cake",					type_cake_dough,cake_dough_yellow,		filling_none,	fruit_blueberry,	coating_glaze,		decoration_none,	spice_none,		shape_torus ) );
	KrispyKreme.push_back( new Donut( "Glazed Sour Cream",						type_cake_dough,cake_dough_sour_cream,	filling_none,	fruit_none,			coating_glaze,		decoration_none,	spice_none,		shape_torus ) );
	KrispyKreme.push_back( new Donut( "Glazed Devil's Food Cake",				type_cake_dough,cake_dough_devils_food,	filling_none,	fruit_none,			coating_glaze,		decoration_none,	spice_none,		shape_torus ) );
	KrispyKreme.push_back( new Donut( "Chocolate Iced Glaze",					type_yeast,		cake_dough_none,		filling_none,	fruit_none,			coating_chocolate,	decoration_none,	spice_none,		shape_torus ) );
	KrispyKreme.push_back( new Donut( "Chocolate Iced Cruller",					type_yeast,		cake_dough_none,		filling_none,	fruit_none,			coating_chocolate,	decoration_none,	spice_none,		shape_cruller ) );
	KrispyKreme.push_back( new Donut( "Chocolate Iced Glaze with Sprinkles",	type_yeast,		cake_dough_none,		filling_none,	fruit_none,			coating_chocolate,	decoration_sprinkles,spice_none,		shape_torus ) );
	KrispyKreme.push_back( new Donut( "Chocolate Iced Creme Filled",			type_yeast,		cake_dough_none,		filling_creme,	fruit_none,			coating_chocolate,	decoration_none,	spice_none,		shape_round ) );
	KrispyKreme.push_back( new Donut( "Chocolate Iced Custard Filled",			type_yeast,		cake_dough_none,		filling_custard,fruit_none,			coating_chocolate,	decoration_none,	spice_none,		shape_round ) );
	KrispyKreme.push_back( new Donut( "Cinnamon Apple Filled",					type_yeast,		cake_dough_none,		filling_fruit,	fruit_apple,		coating_powder,	decoration_none,	spice_cinnamon,	shape_round ) );
	KrispyKreme.push_back( new Donut( "Glazed Creme Filled",					type_yeast,		cake_dough_none,		filling_creme,	fruit_none,			coating_glaze,		decoration_none,	spice_none,		shape_round ) );
	KrispyKreme.push_back( new Donut( "Powdered Strawberry Filled",				type_yeast,		cake_dough_none,		filling_fruit,	fruit_strawberry,	coating_powder,		decoration_none,	spice_none,		shape_round ) );
	KrispyKreme.push_back( new Donut( "Glazed Rasberry Filled",					type_yeast,		cake_dough_none,		filling_fruit,	fruit_rasberry,		coating_glaze,		decoration_none,	spice_none,		shape_round ) );
	KrispyKreme.push_back( new Donut( "Glazed Lemon Filled",					type_yeast,		cake_dough_none,		filling_fruit,	fruit_lemon,		coating_glaze,		decoration_none,	spice_none,		shape_round ) );
	
	while( !bEndProg )
	{
		mySnack = Donut( "My Donut" );
		//donut type
		system("cls");
		iInput = 0;
		std::cout<<"What is the donut made of?\n"
				<<"1: Yeast\n"
				<<"2: Cake Dough\n\n";
		while( iInput < 1 || iInput > 2 )
		{
			iInput = getch() - 48;
		}
		mySnack.Type = iInput - 1;

		if( iInput == 2 )
		{
			//Cake Dough Type
			//system("cls");
			iInput = 0;
			std::cout<<"What kind of cake dough?\n"
					<<"1: Devil's Food Cake\n"
					<<"2: Yellow\n"
					<<"3: Sour Cream\n\n";
			while( iInput < 1 || iInput > 3 )
			{
				iInput = getch() - 48;
			}
			mySnack.CakeDough = iInput;

			if( iInput == 2 )
			{
				mySnack.Fruit = 5;
			}
		}
		else
		{
			//filling
			//system("cls");
			iInput = 0;
			std::cout<<"What filling?\n"
					<<"1: None\n"
					<<"2: Creme\n"
					<<"3: Custard\n"
					<<"4: Fruit\n\n";
			while( iInput < 1 || iInput > 4 )
			{
				iInput = getch() - 48;
			}
			mySnack.Filling = iInput - 1;

			if( iInput != 1 )
			{
				mySnack.Shape = shape_round;
			}

			if( iInput == 4 )
			{
				//system("cls");
				iInput = 0;
				std::cout<<"What fruit?\n"
						<<"1: Apple\n"
						<<"2: Rasberry\n"
						<<"3: Lemon\n"
						<<"4: Strawberry\n\n";
				while( iInput < 1 || iInput > 4 )
				{
					iInput = getch() - 48;
				}
				mySnack.Fruit = iInput;
				if( iInput == 1 || iInput == 4 )
				{
					mySnack.Coating = coating_powder;
				}
				if( iInput == 1 )
				{
					mySnack.Spice = spice_cinnamon;
				}
				iInput = 0;
			}
			else if( iInput == 3 )
			{
				mySnack.Coating = coating_chocolate;
			}
			else if( iInput == 2 )
			{
				//Coating
				//system("cls");
				iInput = 0;
				std::cout<<"What Coating?\n"
						<<"1: Glaze\n"
						<<"2: Chocolate\n\n";
				while( iInput < 1 || iInput > 2 )
				{
					iInput = getch() - 48;
				}
				mySnack.Coating = iInput - 1;
			}
			else
			{
				//Coating
				//system("cls");
				iInput = 0;
				std::cout<<"What Coating?\n"
						<<"1: Glaze\n"
						<<"2: Chocolate\n"
						<<"3: Maple\n\n";
				while( iInput < 1 || iInput > 3 )
				{
					iInput = getch() - 48;
				}
				if( iInput == 3 )
				{
					iInput = 4;
				}
				mySnack.Coating = iInput - 1;

				if( iInput == 1 )
				{
					//Spice
					//system("cls");
					iInput = 0;
					std::cout<<"What Spice?\n"
							<<"1: none\n"
							<<"2: Cinnamon\n\n";
					while( iInput < 1 || iInput > 2 )
					{
						iInput = getch() - 48;
					}
					mySnack.Spice = iInput - 1;
					if( iInput == 1 )
					{
						//Shape
						//system("cls");
						iInput = 0;
						std::cout<<"What Shape?\n"
								<<"1: Torus\n"
								<<"2: Cruller\n\n";
						while( iInput < 1 || iInput > 2 )
						{
							iInput = getch() - 48;
						}
						mySnack.Shape = iInput - 1;
					}
					iInput = 0;
				}
				else if( iInput == 2 )
				{
					//Sprinkles
					//system("cls");
					iInput = 0;
					std::cout<<"Sprinkles?\n"
							<<"1: No\n"
							<<"2: Yes\n\n";
					while( iInput < 1 || iInput > 2 )
					{
						iInput = getch() - 48;
					}
					mySnack.Decoration = iInput - 1;

					if( iInput == 1 )
					{
						//Shape
						//system("cls");
						iInput = 0;
						std::cout<<"What Shape?\n"
								<<"1: Torus\n"
								<<"2: Cruller\n\n";
						while( iInput < 1 || iInput > 2 )
						{
							iInput = getch() - 48;
						}
						if( iInput == 2 )
						{
							mySnack.Shape = 2;
						}
					}
				}
			}
		}
		//system("cls");
		std::cout<<"Get a ";
		for( std::vector< Donut* >::iterator iter_i = KrispyKreme.begin(); iter_i != KrispyKreme.end(); ++iter_i )
		{
			if( (*iter_i)->operator ==( mySnack ) )
			{
				std::cout<<(*iter_i)->operator char *()<<"\n";
			}
		}
		std::cout<<"\nWould you like to try again?\n1: Yes\n2: No";
		iInput = 0;
		while( iInput < 1 || iInput > 2 )
		{
			iInput = getch() - 48;
		}
		if( iInput == 2 )
		{
			bEndProg = true;
		}
	}
}