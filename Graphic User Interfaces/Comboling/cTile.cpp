/*************************************************************************** 
Alberto Martinez
vanilla.frijole@gmail.com
www.PMSoft.org
Copyright(c) 2005 PMSoft 

11/28/2004 

cTile.cpp

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
#include "resource.h"
#include "cField.h"
#include "cTile.h"

/**************************************************************
*   Entry:  tile
*
*    Exit:  values will be equal to those of tile.
*
* Purpose:  logic
*
***************************************************************/
cTile& cTile::operator=(const cTile& tile)
{
	state = tile.state;
	next = tile.next;
	x = tile.x;
	y = tile.y;

	return *this;
}

/**************************************************************
*   Entry:  no requirements
*
*    Exit:  class will be instantiated
*
* Purpose:  constructor
*
***************************************************************/
cTile::cTile()
	  :state(0), x(0), y(0), next(0)
{
}

/**************************************************************
*  
*		Destructor
*
***************************************************************/
cTile::~cTile()
{
}