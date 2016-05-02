#include <iostream>
using std::cout;
#include "Queue.h"
#include "error.h"


int main()
{
	cQueue< int > myQueue(10);
	
	cout<<"\n----- Is it Empty? -----\n";
	cout<<myQueue.isEmpty()<<"\n";

	cout<<"\n----- Is it Full? -----\n";
	cout<<myQueue.isFull()<<"\n";

	cout<<"\n----- Fill the Queue -----\n";
	for(int i = 0; i < 10; i++)
	{
		myQueue.Enqueue(i);
		cout<<i<<": "<<myQueue.Front()<<"\n";
	}

	cout<<"\n----- Copy the Queue -----\n";
	cQueue< int > my2ndQueue(myQueue);
	cout<<"queue copied\n";

	cout<<"\n----- Is it Empty? -----\n";
	cout<<my2ndQueue.isEmpty()<<"\n";

	cout<<"\n----- Is it Full? -----\n";
	cout<<my2ndQueue.isFull()<<"\n";

	cout<<"\n----- Empty the Queue -----\n";
	for(int i = 0; i < 10; i++)
	{
		cout<<i<<": "<<my2ndQueue.Front()<<"\n";
		my2ndQueue.Dequeue();
	}


	cout<<"\n-----Forcing Underflow -----\n";
	try
	{
		my2ndQueue.Dequeue();
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}

	cout<<"\n-----Forcing Overflow -----\n";
	try
	{
		myQueue.Enqueue(100);
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}


	return 0;
}