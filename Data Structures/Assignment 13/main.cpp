//Write a graph class implemented using an adjacency list.
//This will be an undirected graph. Include: breadth-first and depth traversals, and a function to tell the degree of a vertex.

#include<iostream>
using std::cout;
#include "tGraph.h"

int main()
{
	tGraph< int > myGraph;
	try
	{
		cout<<"Adding Graph Nodes\n";
		for(int i = 0; i < 10; i++)
		{
			cout<<i<<"\n";
			myGraph.Insert(i);
		}
		cout<<"Creating links...   ";
		myGraph.Link(0, 1);
		myGraph.Link(1, 2);
		myGraph.Link(1, 6);
		myGraph.Link(2, 3);
		myGraph.Link(3, 4);
		myGraph.Link(4, 5);
		myGraph.Link(5, 6);
		myGraph.Link(6, 7);
		myGraph.Link(7, 8);
		myGraph.Link(7, 9);
		cout<<"links created\n";
		
		cout<<"Removing a node...   ";
		myGraph.Remove(8);
		cout<<"node removed\n";

		cout<<"\nBreadth-First Traversal\n";
		myGraph.BF_Traverse();

		cout<<"\nDepth Traversal\n";
		myGraph.D_Traverse();
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}

}