#ifndef DONUT_H
#define DONUT_H

#include "property.h"

enum enum_donut
{
	original_glazed,
	maple_iced,
	glazed_cinnamon,
	glazedcruller,
	glazed_blueberry_cake,
	glazed_sour_cream,
	glazed_devils_food_cake,
	chocolate_iced_glaze,
	chocolate_iced_cruller,
	chocolate_iced_glaze_with_sprinkles,
	chocolate_iced_cream_filled,
	chocolate_iced_custard_filled,
	cinnamon_apple_filled,
	glazed_creme_filled,
	powdered_strawberry_filled,
	glazed_rasberry_filled,
	glazed_lemon_filled
};

enum enum_type
{
	type_yeast,
	type_cake_dough
};

enum enum_cake_dough
{
	cake_dough_none,
	cake_dough_devils_food,
	cake_dough_yellow,
	cake_dough_sour_cream
};

enum enum_filling
{
	filling_none,
	filling_creme,
	filling_custard,
	filling_fruit
};

enum enum_fruit
{
	fruit_none,
	fruit_apple,
	fruit_rasberry,
	fruit_lemon,
	fruit_strawberry,
	fruit_blueberry
};

enum enum_coating
{
	coating_glaze,
	coating_chocolate,
	coating_powder,
	coating_maple
};

enum enum_decoration
{
	decoration_none,
	decoration_sprinkles
};

enum enum_spice
{
	spice_none,
	spice_cinnamon
};

enum enum_shape
{
	shape_torus,
	shape_round,
	shape_cruller
};

class Donut
{
public:
	Donut( char*, int = type_yeast, int = cake_dough_none, int = filling_none, int = fruit_none, int = coating_glaze, int = decoration_none, int = spice_none, int = shape_torus );
	~Donut();
	bool operator ==( Donut& );
	operator char*();

	Property<int> Type;
	Property<int> CakeDough;
	Property<int> Filling;
	Property<int> Fruit;
	Property<int> Coating;
	Property<int> Decoration;
	Property<int> Spice;
	Property<int> Shape;

private:
	char* strDonutDesc;
	int donType;
	int donCakeDough;
	int donFilling;
	int donFruit;
	int donCoating;
	int donDecoration;
	int donSpice;
	int donShape;
};

#endif