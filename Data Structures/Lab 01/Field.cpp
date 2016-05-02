#include "Field.h"
#include <iostream>
using std::cout;

/**************************************************************
*   Entry:  X x Y type field(no negatives).  Mine_Count > 0 if
*			you want to win.
*
*    Exit:  All members of the field array will have a value.
*
* Purpose:  To create the playing field and place random mines.
*
***************************************************************/
void cField::Populate(int X, int Y, const int& Mine_Count)
{
	Game_Over = false;
	m_mines = Mine_Count;
	m_Squares.SetRows(X);
	m_Squares.SetColumns(Y);

	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{
			m_Squares[i][j].setIdentity(0);
		}
	}

	//Here is where we place mines
	mine_loc.SetRows(Mine_Count);
	mine_loc.SetColumns(2);
	int RTBound=0; 
	int RBBound=0; 
	int CTBound=0; 
	int CBBound=0; 

	for(int i = 0; i < Mine_Count; i++)
	{
		mine_loc[i][0] = Generator.Randomize(0, m_Squares.getRows()-1);
		mine_loc[i][1] = Generator.Randomize(0, m_Squares.getColumns()-1);

		m_Squares[mine_loc[i][0]][mine_loc[i][1]].setIdentity(-1);
 
		RTBound = mine_loc[i][0]-1; 
		RBBound = mine_loc[i][0]+1; 
		CTBound = mine_loc[i][1]-1; 
		CBBound = mine_loc[i][1]+1; 

		if (RTBound < 0)     RTBound=0; 
		if (RBBound >= m_Squares.getRows()) RBBound = m_Squares.getRows()-1; 
		if (CTBound < 0)     CTBound = 0; 
		if (CBBound >= m_Squares.getColumns()) CBBound=m_Squares.getColumns()-1; 

		for(int k=RTBound;k<=RBBound;k++) 
		{ 
			for(int j=CTBound;j<=CBBound;j++) 
			{ 
						++m_Squares[k][j];
			} 
		} 
	}

}

/**************************************************************
*   Entry:  Any
*
*    Exit:  All members of the field array will now be visible.
*
* Purpose:  To show the player where the mines are after the
*			game is over.
***************************************************************/
void cField::ShowAll()
{
	for(int i = 0; i < m_Squares.getRows(); i++)
	{
		for(int j = 0; j < m_Squares.getColumns(); j++)
		{
			m_Squares[i][j].show();
		}
	}
}

/**************************************************************
*   Entry:  X and Y within the bounds of the field.
*
*    Exit:  The square in respect to X and Y will be uncovered
*		and the game will continue or be set as a lost game.
*
* Purpose:  To uncover a square and reveal blanks, mines or
*			number.
***************************************************************/
void cField::Uncover(const int X, const int Y)
{
	if((X > -1) && (X < m_Squares.getRows()))
	{
		if((Y > -1) && (Y < m_Squares.getColumns()))
		{ 
			if ((m_Squares[X][Y].getIdentity()==0) && (m_Squares[X][Y].visible() == true))//if number is 0, check bounds 
			{
				m_Squares[X][Y].show();//uncover

				int RTBound=0; 
				int RBBound=0; 
				int CTBound=0; 
				int CBBound=0; 

				//create bounds for around the square 
				RTBound = X-1; 
				RBBound = X+1; 
				CTBound = Y-1; 
				CBBound = Y+1; 

				//make sure bounds are in the minefield 
				if (RTBound < 0)     RTBound=0; 
				if (RBBound >= m_Squares.getRows()) RBBound = m_Squares.getRows()-1; 
				if (CTBound < 0)     CTBound = 0; 
				if (CBBound >= m_Squares.getColumns()) CBBound=m_Squares.getColumns()-1; 

			
				//check surrounding squares 
				for(int i=RTBound;i<=RBBound;i++) 
				{ 
					for(int j=CTBound;j<=CBBound;j++) 
					{ 
						if (!((i==X) && (j==Y)))//ignore center square 
						{ 
							if (m_Squares[i][j].getIdentity()!= -1) 
								Uncover(i,j);
						} 
					} 
				} 
			}
			m_Squares[X][Y].show();//uncover
			if(m_Squares[X][Y].getIdentity() == -1)
			{
				Game_Over = true;
			}
		}
	}
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  return whether the current game has ended or not.
*
***************************************************************/
bool cField::GameOver()
{
	return Game_Over;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  To return whether the current game has been owned
*
***************************************************************/
bool cField::Did_I_Win()
{
	bool temp(false);

	for(int i = 0; (i < m_mines) && (m_Squares[mine_loc[i][0]][mine_loc[i][1]].getMark()); i++);
	if(i==0) i =1;
	if((i == m_mines) && (m_Squares[mine_loc[i-1][0]][mine_loc[i-1][1]].getMark())) temp = true;

	return temp;
}

/**************************************************************
*   Entry:  X and Y within the bounds of the field.
*
*    Exit:  Square X, Y will be marked or unmarked.
*
* Purpose:  to Mark a mine.  if all Mines are marked then the
*			game has been won.
***************************************************************/
void cField::Mark(int X, int Y)
{
	if((X > -1) && (X < m_Squares.getRows()))
	{
		if((Y > -1) && (Y < m_Squares.getColumns()))
		{ 
			m_Squares[X][Y].mark();
		}
	}
}

/**************************************************************
*   Entry:  All data has been assigned some value.
*
*    Exit:  The current field status will be shown.
*
* Purpose:  To interface with the player
*
***************************************************************/
void cField::PrintField()
{
	system("cls");
	cout<<"/";
	for(int i = 0; i < m_Squares.getRows()*2; i++)
		cout<<"-";
	cout<<"\\\n";

	for(int i = 0; i < m_Squares.getColumns(); i++)
	{
		cout<<"|";//134
		for(int j = 0; j < m_Squares.getRows() * 2; j++)
			cout<<"-";
		cout<<"|\n";

		cout<<"|";
		for(int j = 0; j < m_Squares.getRows(); j++)
			cout<<m_Squares[j][i]<<"|";
		cout<<"|\n";
	}

	cout<<"|";
	for(int j = 0; j < m_Squares.getRows() * 2; j++)
		cout<<"-";
	cout<<"|\n";

	cout<<"\\";
	for(int i = 0; i < m_Squares.getRows() * 2; i++)
		cout<<"-";
	cout<<"/\n";
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  The field will be the "copyme" field.
*
* Purpose:  Copy one field to the other.
*
***************************************************************/
cField& cField::operator=(const cField& copyme)
{
	m_Squares = copyme.m_Squares;
	m_mines = copyme.m_mines;
	return *this;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  Constructs the cField object
*
***************************************************************/
cField::cField()
	   :m_mines(100), m_Squares(16, 30), Game_Over(false), mine_loc(100, 2)
{
	Generator.init_Randomize();
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  cField object will be a copy of "copyme"
*
* Purpose:  copy constructor
*
***************************************************************/
cField::cField(const cField& copyme)
:m_Squares(copyme.m_Squares),
Game_Over(copyme.Game_Over),
mine_loc(copyme.mine_loc),
m_mines(copyme.m_mines)
{
	Generator.init_Randomize();

	*this = copyme;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  default destructor.
*
***************************************************************/
cField::~cField()
{
}