#ifndef TVERTEX_H
#define TVERTEX_H

#include "tLList.h"

template< class T > class tGraph;

template< class T >
class tVertex
{	friend class tGraph;

public:
	~tVertex();
	void Unvisit();

private:
	tVertex(const T& data);

	T m_data;
	bool m_visited;
	tLList< tVertex< T >* > m_vertices;
	
};

template< class T >
void tVertex< T >::Unvisit()
{
	if(m_visited)
	{
		m_visited = !m_visited;
		if( !(m_vertices.isEmpty()) )
		{
			int i(0);
			for(i = 0; m_vertices[i] != m_vertices.Last(); i++)
			{
				m_vertices[i]->Unvisit();
			}
			m_vertices[i]->Unvisit();
		}
	}
}

template< class T >
tVertex< T >::tVertex(const T& data)
			 :m_data(data), m_visited(false)
{
}

//destructor
template< class T >
tVertex< T >::~tVertex()
{
}

#endif