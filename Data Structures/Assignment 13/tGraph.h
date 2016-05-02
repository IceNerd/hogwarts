#ifndef TGRAPH_H
#define TGRAPH_H

#include "tVertex.h"
#include "tQueue.h"
#include "Stack.h"

template< class T >
class tGraph
{public:
	tGraph();
	tGraph(const tGraph&);
	~tGraph();

	void Insert( const T& );
	void Remove( int );
	void BF_Traverse();
	void D_Traverse();
	void Link(int, int);
	void Purge();

	tGraph< T >& operator=(const tGraph< T >& copyme);

private:
	void Link( tVertex< T >*, tVertex< T >* );

	tLList< tVertex< T >* > m_vertices;

};

template< class T >
void tGraph< T >::Purge()
{
	if( !(m_vertices.isEmpty()) )
	{
		int i(0);
		for(i = 0; m_vertices[i] != m_vertices.Last(); i++)
		{
			delete m_vertices[i];
		}
		delete m_vertices[i];
	}
}

template< class T >
tGraph< T >& tGraph< T >::operator=(const tGraph< T >& copyme)
{
	Purge();
	m_vertices = copyme.m_vertices;
}

template< class T >
void tGraph< T >::Insert(const T& data)
{
	int trail(0);
	m_vertices.Append( new tVertex< T >(data) );
	for(trail = 0; m_vertices[trail] != m_vertices.Last(); trail++);
	if(trail > 0)
	{
		Link(m_vertices[trail-1], m_vertices.Last());
	}
}

template< class T >
void tGraph< T >::Remove( int who )
{
	//go through adjacency list
	while( !(m_vertices[who]->m_vertices.isEmpty()) )
	{
		int remove(0);
		for(remove = 0; m_vertices[who]->m_vertices[0]->m_vertices[remove] != m_vertices[who]; remove++);
		m_vertices[who]->m_vertices[0]->m_vertices.Extract(remove);

		m_vertices[who]->m_vertices.Extract(0);
	}
	m_vertices.Extract(who);
}

template< class T >
void tGraph< T >::BF_Traverse()
{
	tQueue< tVertex< T >* > VQ;
	if( !(m_vertices.isEmpty()) )
	{
		VQ.Enqueue(m_vertices.First());
		m_vertices.First()->m_visited = true;
		while( !(VQ.isEmpty()) )
		{
			if( !(VQ.Front()->m_vertices.isEmpty()) )
			{
				int i(0);
				for(i = 0; VQ.Front()->m_vertices[i] != VQ.Front()->m_vertices.Last(); i++)
				{
					if( !(VQ.Front()->m_vertices[i]->m_visited) )
					{
						VQ.Enqueue(VQ.Front()->m_vertices[i]);
						VQ.Front()->m_vertices[i]->m_visited = true;
					}
				}
				if( !(VQ.Front()->m_vertices[i]->m_visited) )
				{
					VQ.Enqueue(VQ.Front()->m_vertices[i]);
					VQ.Front()->m_vertices[i]->m_visited = true;
				}
			}
			cout<<VQ.Front()->m_data<<"\n";
			VQ.Dequeue();
		}
		m_vertices[0]->Unvisit();
	}
}

template< class T >
void tGraph< T >::D_Traverse()
{
	tStack< tVertex< T >* > VStack;

	if( !(m_vertices.isEmpty()) )
	{
		VStack.Push(m_vertices.First());
		m_vertices.First()->m_visited = true;
		while( !(VStack.isEmpty()) )
		{
			cout<<VStack.Peek()->m_data<<"\n";
			tVertex< T >* current(VStack.Peek());
			VStack.Pop();
			if( !(current->m_vertices.isEmpty()) )
			{
				int i(0);
				for(i = 0; current->m_vertices[i] != current->m_vertices.Last(); i++)
				{
					if( !(current->m_vertices[i]->m_visited) )
					{
						VStack.Push(current->m_vertices[i]);
						current->m_vertices[i]->m_visited = true;
						
					}
				}
				if( !(current->m_vertices[i]->m_visited) )
				{
					VStack.Push(current->m_vertices[i]);
					current->m_vertices[i]->m_visited = true;
						
				}
			}
		}
		m_vertices[0]->Unvisit();
	}
}

template< class T >
void tGraph< T >::Link( int Link0, int Link1 )
{
	Link( m_vertices[Link0], m_vertices[Link1] );
}

template< class T >
void tGraph< T >::Link( tVertex< T >* Link0, tVertex< T >* Link1)
{
	if( Link0 && Link1 )
	{
		bool check(false);

		//check link from Link0 to Link1
		if( !(Link0->m_vertices.isEmpty()) )
		{
			int i(0);
			for(i = 0; (Link0->m_vertices[i] != Link0->m_vertices.Last()); i++)
			{
				if(Link0->m_vertices[i] == Link1)
				{
					check = true;
				}
			}
			if(Link0->m_vertices[i] == Link1)
			{
				check = true;
			}
		}
		if(!check)
		{
			Link0->m_vertices.Append(Link1);
		}
		check = false;

		//check link from Link1 to Link0
		if( !(Link1->m_vertices.isEmpty()) )
		{
			int i(0);
			for(i = 0; (Link1->m_vertices[i] != Link1->m_vertices.Last()); i++)
			{
				if(Link1->m_vertices[i] == Link0)
				{
					check = true;
				}
			}
			if(Link1->m_vertices[i] == Link0)
			{
				check = true;
			}
		}
		if(!check)
		{
			Link1->m_vertices.Append(Link0);
		}
		check = false;
	}
	else
	{
		throw EXCEPTION("void Link( tVertex< T >* Link0, tVertex< T >* Link1)^Cannot link^\n");
	}
}

template< class T >
tGraph< T >::tGraph()
{
}

template< class T >
tGraph< T >::tGraph(const tGraph< T >& copyme)
{
	Purge();
	*this = copyme;
}

template< class T >
tGraph< T >::~tGraph()
{
}

#endif