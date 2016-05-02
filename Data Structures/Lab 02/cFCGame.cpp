#include "cFCGame.h"

using std::cout;

/*************************************************************************
*   Entry:  All the arrays have been instantiated and initialized with
*			data.
*
*    Exit:  The table will be printed out.
*
* Purpose:  So that the user can see what is going on in the game.
*
*************************************************************************/
void cFCGame::Display_All()
{
	system("cls");
	cout<<"----- Free Cells ------                         ------ Home Cells ------\n"
		<<"  ";
	for(int i = 0; i < 4; i++)
	{
		if(freecells[i] == 0)
		{
			cout<<"__";
		}
		else
		{
			cout<<*freecells[i];
		}
		cout<<"   ";
	}
	cout<<"                             ";

	for(int i = 0; i < 4; i++)
	{
		if(homecells[i].isEmpty())
		{
			cout<<"__";
		}
		else
		{
			cout<<*homecells[i].Peek();
		}
		cout<<"   ";
	}
	cout<<"\n\n";
	cout<<"------------------------------------------------------------------------\n\n";
	cout<<"              0     1     2     3     4     5     6     7\n"
		<<"            ______________________________________________\n";

	tArray< tStack< cCard* > > temp(8, 0);
	int highest(0);
	for(int i = 0; i < 8; i++)
	{
		int high_check(0);
		while(!table[i].isEmpty())
		{
			temp[i].Push(table[i].Peek());
			table[i].Pop();
			high_check++;
		}
		if(high_check > highest)highest = high_check;
	}

	for(int i = 0; i < highest; i++)
	{
		cout<<i<<":           ";
		for(int j = 0; j < 8; j++)
		{
			if(!temp[j].isEmpty())
			{
				cout<<*temp[j].Peek()<<"    ";
				table[j].Push(temp[j].Peek());
				temp[j].Pop();
			}
			else
			{
				cout<<"      ";
			}
		}
		cout<<"\n\n";
	}
	
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
void cFCGame::Restart()
{
	for(int i = 0; i < 4; i++)
	{
		freecells[i] = 0;
		while(!homecells[i].isEmpty())
		{
			delete homecells[i].Peek();
			homecells[i].Pop();
		}
	}
	
	for(int i = 0; i < 8; i++)
	{
		while(!table[i].isEmpty())
		{
			delete table[i].Peek();
			table[i].Pop();
		}
	}

	Shuffle_Deck();

	for(int i = 0; i < 52;)
	{
		for(int j = 0; i < 52 && j < 8; j++)
		{
			table[j].Push(deck.Peek());
			deck.Pop();
			i++;
		}
	}

	Display_All();
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
void cFCGame::Shuffle_Deck()
{
	Dealer.init_Randomize();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 13; j++)
		{
			deck.Push(new cCard(i, j));
		}
	}

	tArray< cCard* > temp(52, 0);
	for(int i = 0; i < 52; i++)
	{
		temp[i] = deck.Peek();
		deck.Pop();
	}
	
	int rand;
	cCard* swap;
	for(int i = 0; i < 52; i++)
	{
		rand = Dealer.Randomize(0, 51);
		swap = temp[i];
		temp[i] = temp[rand];
		temp[rand] = swap;
	}

	for(int i = 0; i < 52; i++)
	{
		deck.Push(temp[i]);
	}
}

/*************************************************************************
*   Entry:  No requirements needed to start the game.
*
*    Exit:  The game will have been played or the user has chosen to exit
*
* Purpose:  Interface to the user.  This is the main procedure of the game
*
*************************************************************************/
void cFCGame::Game_Start()
{
	bool Game_Over(false);
	int choice(0);

	cout<<"Welcome to Free Cell!!!\n"
		<<"By: Alberto Martinez\n\n"
		<<"Press any key to begin";
	getch();
	Restart();

	while(!Game_Over)
	{
		Display_All();
		cout<<"(M)ove Cards or (Q)uit game?  ";
		choice = getch();
		if( (choice == 113) || (choice == 81) )
		{
			Game_Over = true;
		}
		else if( (choice == 109) || (choice == 77) )
		{
			int from(-1), to(-1);
			cout<<"Move Cards\n";
			cout<<"From (F)ree Cells or (T)able?  ";
			while(from == -1)
			{
				choice = getch();
				if( (choice == 102) || (choice == 70) )
				{
					cout<<"Free Cells\n";
					from = 0;
				}
				else if( (choice == 116) || (choice == 84) )
				{
					cout<<"Table\n";
					from = 1;
				}
			}

			cout<<"To (F)ree Cells, (T)able or (H)ome Cells?  ";
			while(to == -1)
			{
				choice = getch();
				if( (choice == 102) || (choice == 70) )
				{
					cout<<"Free Cells\n";
					to = 0;
				}
				else if( (choice == 116) || (choice == 84) )
				{
					cout<<"Table\n";
					to = 1;
				}
				else if( (choice == 104) || (choice == 72) )
				{
					cout<<"Home Cells\n";
					to = 2;
				}
			}
			if(Move_Card(from, to))
			{
				cout<<"Success!\n";
			}
			else
			{
				cout<<"Failure!\n";
			}
			cout<<"Press any Key to continue";
			getch();
		}
		else
		{
			cout<<"Invalid Choice, please try again";
			getch();
		}
	}
}

/*************************************************************************
*   Entry:  Destination from and destination to has been chosen by the
*			user.
*
*    Exit:  A card will have been moved or a card movement will be
*			rejected.
*
* Purpose:  To move cards.  This is the games main purpose.
*
*************************************************************************/
bool cFCGame::Move_Card(int from, int to)
{
	bool complete(false);
	int xFrom(-1), yFrom(-1), xTo(-1), yTo(-1);

	switch(from)
	{
	case 0:
		switch(to)
		{
		//From Freecell to Freecell
		case 0:
			cout<<"From: 0 1 2 or 3  ";
			while( (xFrom < 0) || (xFrom > 3) )
			{
				xFrom = getch() - 48;
			}
			cout<<xFrom<<"\n"
				<<"To: 0 1 2 or 3  ";
			while( (xTo < 0) || (xTo > 3) )
			{
				xTo = getch() - 48;
			}
			cout<<xTo<<"\n";

			if(freecells[xFrom] == 0)
			{
				cout<<"FreeCell "<<xFrom<<" is Empty!\n";
			}
			else if(freecells[xTo] != 0)
			{
				cout<<"FreeCell "<<xTo<<" already occupied!\n";
			}
			else
			{
				freecells[xTo] = freecells[xFrom];
				freecells[xFrom] = 0;
				complete = true;
			}
		break;

		//From Freecell to Table
		case 1:
			cout<<"From: 0 1 2 or 3  ";
			while( (xFrom < 0) || (xFrom > 3) )
			{
				xFrom = getch() - 48;
			}
			cout<<xFrom<<"\n"
				<<"To: 0 - 7  ";
			while( (xTo < 0) || (xTo > 7) )
			{
				xTo = getch() - 48;
			}
			cout<<xTo<<"\n";

			if(freecells[xFrom] == 0)
			{
				cout<<"FreeCell "<<xFrom<<" is Empty!\n";
			}
			else
			{
				if(freecells[xFrom]->getRank() == table[xTo].Peek()->getRank() - 1)
				{
					if(freecells[xFrom]->getColor() != table[xTo].Peek()->getColor())
					{
						table[xTo].Push(freecells[xFrom]);
						freecells[xFrom] = 0;
						complete = true;
					}
				}
			}
		break;
		
		//From Freecell to Home Cell
		case 2:
			cout<<"From: 0 1 2 or 3  ";
			while( (xFrom < 0) || (xFrom > 3) )
			{
				xFrom = getch() - 48;
			}

			if(freecells[xFrom] == 0)
			{
				cout<<"FreeCell "<<xFrom<<" is Empty!\n";
			}
			else
			{
				if(homecells[freecells[xFrom]->getSuit()].isEmpty())
				{
					if(freecells[xFrom]->getRank() == 0)
					{
						homecells[freecells[xFrom]->getSuit()].Push(freecells[xFrom]);
						freecells[xFrom] = 0;
						complete = true;
					}
				}
				else
				{
					if(freecells[xFrom]->getRank() == homecells[freecells[xFrom]->getSuit()].Peek()->getRank() + 1)
					{
						homecells[freecells[xFrom]->getSuit()].Push(freecells[xFrom]);
						freecells[xFrom] = 0;
						complete = true;
					}
				}
			}

		break;

		default:
		break;
		}
	break;

	case 1:
		switch(to)
		{
		//From Table to Freecell
		case 0:
			cout<<"From: 0 - 7  ";
			while( (xFrom < 0) || (xFrom > 7) )
			{
				xFrom = getch() - 48;
			}
			cout<<xFrom<<"\n"
				<<"To: 0 1 2 or 3  ";
			while( (xTo < 0) || (xTo > 3) )
			{
				xTo = getch() - 48;
			}
			cout<<xTo<<"\n";

			if(table[xFrom].isEmpty())
			{
				cout<<"Table Stack "<<xFrom<<" is Empty!\n";
			}
			else if(freecells[xTo] != 0)
			{
				cout<<"FreeCell "<<xTo<<" already occupied!\n";
			}
			else
			{
				freecells[xTo] = table[xFrom].Peek();
				table[xFrom].Pop();
				complete = true;
			}
		break;
		
		//From Table to Table (this is the big one
		//Stacks are allowed to move, however, they are
		//"normal" moves.  The available freecells must
		//be used when needed.  No more than the
		//freecells will be used.  No Temporary variables.
		case 1:
			cout<<"From: 0 - 7  ";
			while( (xFrom < 0) || (xFrom > 7) )
			{
				xFrom = getch() - 48;
			}
			cout<<xFrom<<"\n"
				<<"To: 0 - 7  ";
			while( (xTo < 0) || (xTo > 7) )
			{
				xTo = getch() - 48;
			}
			cout<<xTo<<"\n";

			if(table[xFrom].isEmpty())
			{
				cout<<"Table "<<xFrom<<" is Empty!\n";
			}
			else if(table[xFrom].Peek() == table[xTo].Peek())
			{
				complete = true;
			}
			else
			{

				//Single Move
				if(!table[xTo].isEmpty())
				{
					if(table[xFrom].Peek()->getRank() == table[xTo].Peek()->getRank() - 1)
					{
						if(table[xFrom].Peek()->getColor() != table[xTo].Peek()->getColor())
						{
							table[xTo].Push(table[xFrom].Peek());
							table[xFrom].Pop();
							complete = true;
						}
					}
				}
				else
				{
					table[xTo].Push(table[xFrom].Peek());
					table[xFrom].Pop();
					complete = true;
				}
				//end Single Move

				//Stack Move
				if(!complete)
				{
					int moves(1), count(0);
					tStack< cCard* > temp;

					for(int i = 0; i < 4; i++)
					{
						if(freecells[i] == 0)
						{
							moves++;
						}
					}
						
					count = moves;
					while( (moves > 0)
							&&
							(table[xFrom].Peek()->getRank() != table[xTo].Peek()->getRank() - 1)
							&&
							(!table[xFrom].isEmpty())
							)
					{//while
						moves--;
						temp.Push(table[xFrom].Peek());
						table[xFrom].Pop();
					}//end while

					if(!table[xFrom].isEmpty())
					{
						if( (table[xFrom].Peek()->getRank() == table[xTo].Peek()->getRank() - 1)
							&&
							(table[xFrom].Peek()->getColor() != table[xTo].Peek()->getColor())
						   )
						{
							bool color_check(true);
							int color_checker(table[xFrom].Peek()->getColor());
							tStack< cCard* > color_temp;
							while(!temp.isEmpty())
							{
								color_temp.Push(temp.Peek());
								if(color_checker != temp.Peek()->getColor())
								{
									color_check = false;
								}

								if(color_check == 0)
								{
									color_check = 1;
								}
								else
								{
									color_check = 0;
								}
								temp.Pop();
							}

							while(!color_temp.isEmpty())
							{
								temp.Push(color_temp.Peek());
								color_temp.Pop();
							}
							
							if(color_check)
							{
								table[xTo].Push(table[xFrom].Peek());
								table[xFrom].Pop();
								while(!temp.isEmpty())
								{
									table[xTo].Push(temp.Peek());
									temp.Pop();
								}
								complete = true;
							}
							else
							{
								while(!temp.isEmpty())
								{
									table[xFrom].Push(temp.Peek());
									temp.Pop();
								}
							}
						}
						else
						{
							while(!temp.isEmpty())
							{
								table[xFrom].Push(temp.Peek());
								temp.Pop();
							}
						}
					}
					else
						{
							while(!temp.isEmpty())
							{
								table[xFrom].Push(temp.Peek());
								temp.Pop();
							}
						}
				}
				//end Stack Move
			}
		break;

		//From Table to HomeCells
		case 2:
			cout<<"From: 0 - 7  ";
			while( (xFrom < 0) || (xFrom > 7) )
			{
				xFrom = getch() - 48;
			}
			cout<<xFrom<<"\n";

			if(table[xFrom].isEmpty())
			{
				cout<<"Table Column "<<xFrom<<" is Empty!\n";
			}
			else
			{
				if(homecells[table[xFrom].Peek()->getSuit()].isEmpty())
				{
					if(table[xFrom].Peek()->getRank() == 0)
					{
						homecells[table[xFrom].Peek()->getSuit()].Push(table[xFrom].Peek());
						table[xFrom].Pop();
						complete = true;
					}
				}
				else
				{
					if(table[xFrom].Peek()->getRank() == homecells[table[xFrom].Peek()->getSuit()].Peek()->getRank() + 1)
					{
						homecells[table[xFrom].Peek()->getSuit()].Push(table[xFrom].Peek());
						table[xFrom].Pop();
						complete = true;
					}
				}
			}
		break;

		}
	break;

	default:
		complete = false;
	break;
	}

	return complete;
}


//----- CTors and DTors --------------------------------------------------

/*************************************************************************
*   Entry:  n/a
*
*    Exit:  Array Sizes are set.
*
* Purpose:  Instantiate the game class.
*
*************************************************************************/
cFCGame::cFCGame()
	:homecells(4,0), freecells(4,0), table(8, 0)
{
}

/*************************************************************************
*   Entry:  n/a
*
*    Exit:  Game class is destroyed.
*
* Purpose:  To destroy the game class.
*
*************************************************************************/
cFCGame::~cFCGame()
{
}