#include "cSPath.h"
#include "tQueue.h"
#include "Stack.h"
#include <iostream>
using std::cout;

#include<fstream>
using std::ifstream;

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
void cSPath::Short_Path(const int& from, const int& to)
{
	tQueue< cSPNode* > BQ;
	Reset_Distance();

	m_verts[from]->m_TDist = 0;
	m_verts[from]->visited = true;
	m_verts[from]->predecessor = -1;
	int i(0);
	for(i = 0; m_verts[from]->m_arcs[i] != m_verts[from]->m_arcs.Last(); i++)
	{
		BQ.Enqueue(m_verts[from]->m_arcs[i]->m_dest);
		m_verts[from]->m_arcs[i]->m_dest->m_TDist = m_verts[from]->m_arcs[i]->m_weight;
		m_verts[from]->m_arcs[i]->m_dest->predecessor = from;
	}
	BQ.Enqueue(m_verts[from]->m_arcs[i]->m_dest);
	m_verts[from]->m_arcs[i]->m_dest->m_TDist = m_verts[from]->m_arcs[i]->m_weight;
	m_verts[from]->m_arcs[i]->m_dest->predecessor = from;

	while( !(BQ.isEmpty()) )
	{
		int pivot(FindIndex(BQ.Front()));
		if( !(BQ.Front()->m_arcs.isEmpty()) )
		{
			for(i = 0; m_verts[pivot]->m_arcs[i] != m_verts[pivot]->m_arcs.Last(); i++)
			{
				if( !(m_verts[pivot]->m_arcs[i]->m_dest->visited) )
				{
					BQ.Enqueue(m_verts[pivot]->m_arcs[i]->m_dest);

					if( (m_verts[pivot]->m_arcs[i]->m_dest->m_TDist) < (m_verts[pivot]->m_TDist + m_verts[pivot]->m_arcs[i]->m_weight) )
					{
						m_verts[pivot]->m_arcs[i]->m_dest->m_TDist = m_verts[pivot]->m_TDist + m_verts[pivot]->m_arcs[i]->m_weight;
						m_verts[pivot]->m_arcs[i]->m_dest->predecessor = pivot;
					}
				}
			}

			if( !(m_verts[pivot]->m_arcs[i]->m_dest->visited) )
			{
				BQ.Enqueue(m_verts[pivot]->m_arcs[i]->m_dest);

				if( (m_verts[pivot]->m_arcs[i]->m_dest->m_TDist) < (m_verts[pivot]->m_TDist + m_verts[pivot]->m_arcs[i]->m_weight) )
				{
					m_verts[pivot]->m_arcs[i]->m_dest->m_TDist = m_verts[pivot]->m_TDist + m_verts[pivot]->m_arcs[i]->m_weight;
					m_verts[pivot]->m_arcs[i]->m_dest->predecessor = pivot;
				}
			}

		}
		BQ.Front()->visited = true;
		BQ.Dequeue();
	}

	//follow predecessor Array;
	i = to;
	tStack< cSPNode* > tripStack;
	while( i != -1 )
	{
		tripStack.Push(m_verts[i]);
		i = m_verts[i]->predecessor;
	}
	

	//Let's Print out the info we have collected
	float ETA(0);
	while( !(tripStack.isEmpty()) )
	{
		cSPNode* trail(tripStack.Peek());
		tripStack.Pop();
		cSPArc* curPath(0);
		cout<<trail->m_desc<<"\n";
		if( !(tripStack.isEmpty()) )
		{
			curPath = trail->FindArc(tripStack.Peek()->m_desc);
			cout<<"via: "<<curPath->m_desc<<"\n";
			if(curPath->m_desc == "I-5")
			{
				ETA += float(curPath->m_weight) / 65;
			}
			else
			{
				ETA += float(curPath->m_weight) / 55;
			}
		}
		if( !(tripStack.isEmpty()) )
		{
			cout<<" to\n";
		}
		else
		{
			cout<<"\n";
		}
	}
	cout<<"Estimated Drive Time:  "<<ETA<<" hours\n";
	cout<<"Total Distance:  "<<m_verts[to]->m_TDist<<" miles\n";

}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
int cSPath::FindIndex(cSPNode* who)
{
	int returnvalue(0);

	if( !(m_verts.isEmpty()) )
	{
		int i(0);
		for(i = 0; ( (m_verts[i] != m_verts.Last()) && (m_verts[i] != who) ); i++)
		{
			if( m_verts[i] == who )
			{
				returnvalue = i;
			}
		}

		if( m_verts[i] == who )
		{
			returnvalue = i;
		}
	}

	return returnvalue;
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
void cSPath::Reset_Distance()
{
	if( !(m_verts.isEmpty()) )
	{
		int i(0);
		for(i = 0; m_verts[i]!=m_verts.Last(); i++)
		{
			m_verts[i]->m_TDist = -1;
			m_verts[i]->predecessor = -1;
			m_verts[i]->visited = false;
		}
		m_verts[i]->m_TDist = -1;
		m_verts[i]->predecessor = -1;
		m_verts[i]->visited = false;
	}
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
void cSPath::PrintPlaces()
{
	if( !(m_verts.isEmpty()) )
	{
		int i(0);
		for(i = 0; m_verts[i] != m_verts.Last(); i++)
		{
			cout<<i<<": "<<m_verts[i]->m_desc<<"\n";
		}
		cout<<i<<": "<<m_verts[i]->m_desc<<"\n";
	}
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
void cSPath::Insert(const String& desc)
{
	if( !(m_verts.isEmpty()) )
	{
		if( KeySearch(desc) == 0 )
		{
			m_verts.Append( new cSPNode(desc) );
		}
	}
	else
	{
		m_verts.Append( new cSPNode(desc) );
	}
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
cSPNode* cSPath::KeySearch(const String& desc)
{
	cSPNode* returnvalue(0);

	if( !(m_verts.isEmpty()) )
	{
		int i(0);
		for(i = 0; ( (m_verts[i] != m_verts.Last()) && (m_verts[i]->m_desc != desc) ); i++)
		{
			if( m_verts[i]->m_desc == desc )
			{
				returnvalue = m_verts[i];
			}
		}

		if( m_verts[i]->m_desc == desc )
		{
			returnvalue = m_verts[i];
		}
	}

	return returnvalue;
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
cSPath::cSPath(const String& filepath)
{
	ifstream infile;

		char StartNode[256] = "StartNode";
		char EndNode[256];
		char Path[256];
		int Mileage;
		char temp[256];

	infile.open(filepath);
	if(infile.is_open())
	{

		while( !(infile.eof()) && (strcmp(StartNode, "")) )
		{
			infile.getline(StartNode, 256, ',');
			if( strcmp(StartNode, "") )
			{
				infile.getline(EndNode, 256, ',');
				infile.getline(Path, 256, ',');
				infile>>Mileage;

				infile.getline(temp, 256, '\n');


				//construct our tree
				if( KeySearch(StartNode) == 0 )
				{
					m_verts.Append( new cSPNode(StartNode) );
				}
				if( KeySearch(EndNode) == 0 )
				{
					m_verts.Append( new cSPNode(EndNode) );
				}
				KeySearch(StartNode)->InsertArc(Path, Mileage, KeySearch(EndNode) );
				KeySearch(EndNode)->InsertArc(Path, Mileage, KeySearch(StartNode) );
			}

		}
		infile.close();
	}
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
cSPath::~cSPath()
{
}