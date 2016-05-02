#include<iostream>
using std::cout;

#include "tHTable.h"
#include<conio.h>

int main()
{
	tHTable< int, int > myTable(25);
	try
	{
		myTable.Insert(9023, 67);
		myTable.Insert(8525, 0);
		myTable.Insert(5101, 1);
		myTable.Insert(7679, 4);
		myTable.Insert(9726, 1);
		myTable.Insert(3452, 2);

		myTable.Enumerate();

		cout<<"press any key to perform a delete of key 9023, rehash to 23 and change value at key 5101 to 20\n";
		getch();
		myTable.Delete(9023);
		myTable[5101] = 20;
		myTable.ReHash(23);
		myTable.Enumerate();

	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}


}