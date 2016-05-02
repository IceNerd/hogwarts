/*************************************************************************** 
Alberto Martinez
vanilla.frijole@gmail.com
www.PMSoft.org
Copyright(c) 2005 PMSoft 

11/28/2004 

cField.h

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
/************************************************************************
* Class: cField
*
* Constructors:	
*	cField()
*	
*************************************************************************/

#ifndef CFIELD_H
#define CFIELD_H

#include "C2DVector.h"
class cTile;

class cField
{public:
	//Constructors and Destructors
	cField();
	~cField();

	//Mutators
	void Init(int, int);
	void DrawBlankFieldOnVDC();
	void DrawFieldOnVDC();
	void DumpToHDC(const HDC&);
	void MakePuzzle(int);
	void Update(int, int);
	void ResetField();
	bool Click(LPARAM);

	//Methods
	bool CheckWin();

private:
	//Private Class Methods
	bool Collision(int, int, int, int);

	//Class Private Variables
	bool ready;
	int Level;
	int WIN_X;
	int WIN_Y;
	int PivotX;
	int PivotY;
	HDC vdc;	//This is the memory device that will be drawn to
	HDC cdc;	//This is the canvas device where the tiles will be stored for use.
	C2DVector< cTile > field;
};

#endif