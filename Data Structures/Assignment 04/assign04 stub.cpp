#include "Error.h"
#include <iostream>
using std::cout;
#include "cLList.h"

void TestAppend(cLList<int> & alist);
void TestFirstAndLast(const cLList<int> & alist);
void TestPrepend(cLList<int> & alist);
void TestPurge(cLList<int> alist);
void TestInsertBefore();
void TestInsertAfter();
void TestExtract();

void main()
{
	// Tests Canonical Functions
	cLList<int> alist;			//ctor
	cLList<int> blist(alist);		//copy ctor
	cLList<int> clist;

	clist = blist;							//= operator

	// Tests Mutators
	//ok I did this time,  if you wish to see my first() and last() methods
	//handle an empty list by themselves then I will do so, no problem doing that either.
	//Just going for the "no ouptut from the class" approach.  Please let me know if
	//this is ok.  Excluded them at first because first() and last() were used later in
	//the stub.  -Thank you
	try
	{
	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}

	// Tests Methods
	
	TestAppend(alist);
	alist.PrintForwards();
	alist.PrintBackwards();

	TestFirstAndLast(alist);
	TestPrepend(alist);
	TestPurge(alist);
	TestInsertBefore();
	TestInsertAfter();
	TestExtract();

	std::cout << "\n********** List Integrity **********" << std::endl;
	alist.PrintForwards();
	alist.PrintBackwards();
}
void TestAppend(cLList<int> & alist)
{
	std::cout << "\n********** Append **********" << std::endl;

	alist.Append(5);
	alist.Append(15);
	alist.Append(25);
	alist.Append(35);
}
void TestFirstAndLast(const cLList<int> & alist)
{
	cLList<int> blist;

	std::cout << "\n********** First and Last **********" << std::endl;

	// Full List
	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;

	// Empty List
	try
	{
		std::cout << blist.First() << std::endl;
	}
	catch (EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
	try
	{
		std::cout << blist.Last() << std::endl;
	}
	catch (EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
}
void TestPrepend(cLList<int> & alist)
{
	cLList<int> blist;

	std::cout << "\n********** Prepend **********" << std::endl;
	
	// Full List
	alist.Prepend(4);
	alist.Prepend(3);
	alist.Prepend(2);
	alist.Prepend(1);
	alist.Prepend(0);

	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;

	// Empty List
	blist.Prepend(100);
	blist.Prepend(200);
	blist.Prepend(300);
	blist.Prepend(400);
	blist.Prepend(500);

	std::cout << blist.getHead() << std::endl;
	std::cout << blist.getTail() << std::endl;
}
void TestPurge(cLList<int> alist)
{
	std::cout << "\n********** Purge **********" << std::endl;

	std::cout << alist.getHead() << std::endl;
	std::cout << alist.getTail() << std::endl;

	alist.Purge();

	std::cout << alist.getHead() << std::endl;
	std::cout << alist.getTail() << std::endl;
}
void TestInsertBefore()
{
	cLList<int> clist;

	std::cout << "\n********** InsertBefore **********" << std::endl;

	// Empty List
	try
	{
		clist.InsertBefore(-1, 0);
	}
	catch(EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
    // Head and Tail are the same
	clist.Append(0);
	clist.InsertBefore(-1, 0);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

    // Before Head
	clist.InsertBefore(-3, -1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

    // Middle
	clist.InsertBefore(-2, -1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	// Node doesn't exist
	try
	{
		clist.InsertBefore(-2, 99);
	}
	catch (EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
}
void TestInsertAfter()
{
	cLList<int> clist;

	std::cout << "\n********** InsertAfter **********" << std::endl;

	try
	{
		clist.InsertAfter(-1, 0);
	}
	catch(EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
    // Head and Tail are the same
	clist.Append(0);
	clist.InsertAfter(1, 0);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

    // After Tail
	clist.InsertAfter(3, 1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

    // Middle
	clist.InsertAfter(2, 1);

	std::cout << clist.First() << std::endl;
	std::cout << clist.Last() << std::endl;

	// Node doesn't exist
	try
	{
		clist.InsertAfter(-2, 99);
	}
	catch (EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
}
void TestExtract()
{
	cLList<int> alist;

	std::cout << "\n********** Extract **********" << std::endl;

	// Empty List
	try
	{
		alist.Extract(0);
	}
	catch (EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
	// Head and Tail are the same
	alist.Append(0);
	alist.Extract(0);

	try
	{
		std::cout << alist.First() << std::endl;
	}
	catch (EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}
	try
	{
		std::cout << alist.Last() << std::endl;
	}
	catch (EXCEPTION& msg)
	{
		std::cout << msg << std::endl;
	}

	// Remove Head
	alist.Append(0);
	alist.Append(1);
	alist.Extract(0);

	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;

	// Remove Tail
	alist.Prepend(0);
	alist.Extract(1);

	std::cout << alist.First() << std::endl;
	std::cout << alist.Last() << std::endl;
}