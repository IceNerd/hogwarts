#include "Stack.h"
#include <iostream>
using std::cout;
#include "error.h"

int main()
{
	cStack< int > MyStack;

	cout<<"----- Is the Stack empty? -----\n";
	cout<<MyStack.isEmpty()<<"\n";

	cout<<"\n----- Load Stack with some data -----\n";
	for(int i = 0; i < 5; i++)
	{
		MyStack.Push(i);
		cout<<i<<": "<<MyStack.Peek()<<"\n";
	}

	cout<<"\n----- Copy the Stack -----\n";
	cStack< int > MyStack2(MyStack);
	cout<<"copied Stack of size: "<<MyStack2.Size()<<"\n";

	cout<<"\n----- Add more to the newly made Stack -----\n";
	for(int i = 5; i < 10; i++)
	{
		MyStack2.Push(i);
		cout<<i<<": "<<MyStack2.Peek()<<"\n";
	}

	cout<<"\n----- Is the Stack empty? -----\n";
	cout<<MyStack2.isEmpty()<<"\n";

	cout<<"\n----- Pop 5 -----\n";
	for(int i = 0; i < 5; i++)
	{
		cout<<MyStack2.Size()<<": "<<MyStack2.Peek()<<"\n";
		MyStack2.Pop();
	}

	cout<<"\n----- Force UnderFlow (Popping 100 times)-----\n";
	try
	{
		for(int i = 0; i < 100; i++)
		{
			MyStack2.Pop();
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}

	return 0;
}