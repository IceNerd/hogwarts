/*************************************************************************** 
Alberto Martinez
vanilla.frijole@gmail.com
www.PMSoft.org
Copyright(c) 2005 PMSoft 

11/28/2004 

cField.cpp

This program does NOT abide by the PMSoft coding standards.  This program
was developed before the coding standards were applicable.
***************************************************************************/ 

/*************************************************************************** 
Comboling
Copyright(c) 2005 PMSoft 

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation; either version 2 
of the License, or (at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License 
along with this program; if not, write to the Free Software 
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA." 
***************************************************************************/ 
#include<windows.h>
#include <math.h>
#include "resource.h"
#include "cTile.h"
#include "cField.h"
#include "random.h"

/**************************************************************
*   Entry:  No requirements
*
*    Exit:  VDC will have a blank field drawn on it
*
* Purpose:  clear any drawings or used to show inactive game
*
***************************************************************/
void cField::DrawBlankFieldOnVDC()
{
	BitBlt(vdc, 0, 0, WIN_X, WIN_Y, NULL, 0, 0, BLACKNESS);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			BitBlt(vdc, field[j][i].x, field[j][i].y, 50, 50, cdc, 0, 0, SRCCOPY);
		}
	}
}

/**************************************************************
*   Entry:  No Requirements
*
*    Exit:  VDC will have field drawn with all tiles at their
*		designated value.  Level text will be shown.
*
* Purpose:  Drawn the field for player to see.
*
***************************************************************/
void cField::DrawFieldOnVDC()
{
	TCHAR szBuffer[25];
	BitBlt(vdc, 0, 0, WIN_X, WIN_Y, NULL, 0, 0, BLACKNESS);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			BitBlt(vdc, field[j][i].x, field[j][i].y, 50, 50, cdc, field[j][i].state * 50, 0, SRCCOPY);
		}
	}
	SetTextColor(vdc, RGB(255, 0, 0));
	SetBkColor(vdc, RGB(0, 0, 0));
	TextOut(vdc, 365, 525, szBuffer, wsprintf(szBuffer, TEXT("%5d"), Level));
	TextOut(vdc, 330, 525, "Level:", 6);
}

/**************************************************************
*   Entry:  LvL must be greater than 0.
*
*    Exit:  Tiles will be randomly placed (state set to 1) in
*		such an order that will yield a solvable puzzle.
*
* Purpose:  To create the puzzle.
*
***************************************************************/
void cField::MakePuzzle(int LvL)
{
	int X( Random::Randomize(0, 9) );
	int Y( Random::Randomize(0, 9) );

	int Rise(0);
	int Run(0);
	int StepX(0);
	int StepY(0);
	int Distance(0);
	int RandDistance(0);
	int LastRise(Rise);
	int LastRun(Run);

	//Clear the field
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			field[i][j].state = 0;
		}
	}

	//First random tile
	field[X][Y].state = 1;

	//Make the rest of the tiles
	for(int i = 0; i < LvL; i++)
	{
		//find the direction of where we are going
		while( ((Rise == 0) && (Run == 0)) || ((Rise == LastRise) && (Run == LastRun)) )
		{
			Rise = Random::Randomize(-1, 1);
			Run = Random::Randomize(-1, 1);
			if( ((X == 0) && (Run == -1)) || ((X == 9) && (Run == 1)) || ((Y == 0) && (Rise == -1)) || ((Y == 9) && (Rise == 1)) )
			{
				Rise = 0;
				Run = 0;
			}
		}

		//find our maximum distance
		Distance = 0;
		StepX = X;
		StepY = Y;
		while( (StepX < 10) && (StepX > -1) && (StepY < 10) && (StepY > -1) )
		{
			Distance++;
			StepX = X + (Run * Distance);
			StepY = Y + (Rise * Distance);
		}
		Distance--;
		
		//Random inbetween our current X, Y and Max Distance
		RandDistance = Random::Randomize(1, Distance);

		//Change the state of the tile or go through the loop again
		if( field[X + (Run * RandDistance)][Y + (Rise * RandDistance)].state == 0 )
		{
			X += (Run * RandDistance);
			Y += (Rise * RandDistance);
			field[X][Y].state = 1;
			LastRise = -Rise;
			LastRun = -Run;
			Run = 0;
			Rise = 0;
		}
		else
		{
			Rise = 0;
			Run = 0;
			i--;
		}

	}
	PivotX = -1;
	PivotY = -1;
	Level = LvL;
	DrawFieldOnVDC();
}

/**************************************************************
*   Entry:  Arguments must be within the field.  0 - 9
*
*    Exit:  true if collision exists else false.
*
* Purpose:  See if a tile selection is valid.
*
***************************************************************/
bool cField::Collision(int XStart, int YStart, int XEmpty, int YEmpty)
{
	int LR(0);
	int UD(0);
	int countX(0);
	int countY(0);
	int rise(YStart - YEmpty);
	int run (XStart - XEmpty);
	float temp(0);
	bool isCollision(false);

	if( (rise != 0) && (run != 0) )
	{
		temp = float(rise)/float(run);
		if( abs(temp) != 1.00 )
		{
			isCollision = true;
		}
	}

	if(rise < 0)
	{
		UD = 1;
	}
	else if(rise > 0)
	{
		UD = -1;
	}

	if(run < 0)
	{
		LR = 1;
	}
	else if(run > 0)
	{
		LR = -1;
	}

	countX = XStart;
	countY = YStart;
	while(isCollision == false)
	{
		countX += LR;
		countY += UD;
		if( ( ((countX < 10) && (countX > -1)) && ((countY < 10) && (countY > -1)) ) )
		{
			if(field[countX][countY].state != 0)
			{
				isCollision = true;
			}
		}
		else
		{
			isCollision = true;
		}
	}

	if( (countX == XEmpty) && (countY == YEmpty) )
	{
		if(field[countX][countY].state == 1)
		{
			isCollision = false;
		}
	}

	return isCollision;
}

/**************************************************************
*   Entry:  hdc
*
*    Exit:  hdc will have the vdc bitblt'd to it.
*
* Purpose:  update the hdc
*
***************************************************************/
void cField::DumpToHDC(const HDC& hdc)
{
	BitBlt(hdc, 0, 0, WIN_X, WIN_Y, vdc, 0, 0, SRCCOPY);
}

/**************************************************************
*   Entry:  lParam
*
*    Exit:  true if valid click, false if not.
*
* Purpose:  This is the means through which the field and the
*		user interact.
*
***************************************************************/
bool cField::Click(LPARAM lParam)
{
	HPEN hPen;
	bool valid(false);
	int LSX;
	int LSY;
	int LEX;
	int LEY;

	int X( (( LOWORD(lParam) - 10 ) / 50) );
	int Y( (( HIWORD(lParam) - 10 ) / 50) );

	if( LOWORD(lParam) < 10)
	{
		X = -1;
	}

	if( HIWORD(lParam) < 10 )
	{
		Y = -1;
	}
	
	if( (X >= 0) && (X <= 9) && (Y >= 0) && (Y <= 9) )
	{
		if( PivotX != -1 )
		{
			if( !Collision(PivotX, PivotY, X, Y) )
			{
				if(field[X][Y].state == 1)
				{
					field[X][Y].state = 2;
					Update(X, Y);

					//Draw line
					LSX = 35 + (PivotX*50);
					LSY = 35 + (PivotY*50);
					LEX = 35 + (X*50);
					LEY = 35 + (Y*50);
					hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
					SelectObject(vdc, hPen);  
					MoveToEx(vdc, LSX, LSY, NULL);
					LineTo(vdc, LEX, LEY);
					//Done drawing line on VDC

					PivotX = X;
					PivotY = Y;
					valid = true;
				}
				else
				{
					valid = false;
				}
			}
			else
			{
				valid = false;
			}
		}
		else
		{
			if(field[X][Y].state == 1)
			{
				field[X][Y].state = 3;
				PivotX = X;
				PivotY = Y;
				Update(X, Y);
				valid = true;
			}
			else
			{
				valid = false;
			}
		}
	}

	return valid;
}

/**************************************************************
*   Entry:  X and Y within scope of the field.
*
*    Exit:  Tile will be updated on the vdc.
*
* Purpose:  Update tile on vdc to avoid drawing everything
*
***************************************************************/
void cField::Update(int X, int Y)
{
	BitBlt(vdc, field[X][Y].x, field[X][Y].y, 50, 50, cdc, field[X][Y].state * 50, 0, SRCCOPY);
}

/**************************************************************
*   Entry:  no requirements
*
*    Exit:  true is the puzzle is solved. False if not.
*
* Purpose:  Check to see if the puzzle is solved.
*
***************************************************************/
bool cField::CheckWin()
{
	bool YaY(true);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(field[i][j].state == 1)
			{
				YaY = false;
			}
		}
	}
	return YaY;
}

/**************************************************************
*   Entry:  no Requirements
*
*    Exit:  all tiles that are not 0 will be set to 1.
*
* Purpose:  Resets the field so the user can try solving a
*		different way.
*
***************************************************************/
void cField::ResetField()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if( (field[i][j].state == 2) || (field[i][j].state == 3))
			{
				field[i][j].state = 1;
			}
		}
	}
	PivotX = -1;
	PivotY = -1;
	DrawFieldOnVDC();
}

/**************************************************************
*   Entry:  Size of window
*
*    Exit:  vdc will be initiated
*
* Purpose:  dont want to make too big of a vdc
*
***************************************************************/
void cField::Init(int X, int Y)
{
	if(!ready)
	{
		vdc = CreateCompatibleDC(GetDC(0));
		SelectObject(vdc, CreateCompatibleBitmap(GetDC(0), X, Y));
		WIN_X = X;
		WIN_Y = Y;
	}
}

/**************************************************************
*   Entry:  no requirements
*
*    Exit:  field will be setup for gameplay
*
* Purpose:  constructor to the class
*
***************************************************************/
cField::cField()
	   :field(10, 10), ready(false), PivotX(-1), PivotY(-1)
{
	Random::init_Randomize();
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			field[j][i].x = 10 + (j*50);
			field[j][i].y = 10 + (i*50);
		}
	}

	cdc = CreateCompatibleDC(GetDC(0));
	SelectObject(cdc, LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(TILE_DEFAULT)));
}

/**************************************************************
* 
*	Destructor
*
***************************************************************/
cField::~cField()
{
}