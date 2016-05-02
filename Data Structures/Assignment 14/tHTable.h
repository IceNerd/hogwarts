#ifndef THTABLE_H
#define THTABLE_H

#include "tHNode.h"
#include "tLList.h"
#include "tArray.h"

template< class K, class V >
class tHTable
{public:
	tHTable(const int&);
	~tHTable();

	void Insert(K, V);
	void Delete(K);
	V& Retrieve(K);
	void Update(K, V);
	void Enumerate();
	void ReHash(int);
	V& operator[](K);

private:
	tHNode< K, V >* getLocation(K);
	tArray< tLList< tHNode< K, V >* > > Table;

};

template< class K, class V >
void tHTable< K, V >::Insert(K key, V value)
{
	int bucket(key % Table.getLength());

	Table[bucket].Append( new tHNode< K, V >(key, value) );
}

template< class K, class V >
void tHTable< K, V >::Delete(K key)
{
	int bucket( key % Table.getLength() );
	bool found(false);

	if( !(Table[bucket].isEmpty()) )
	{
		for(int i = 0; (Table[bucket][i] != Table[bucket].Last()) && (!found); i++)
		{
			if(Table[bucket][i]->key == key)
			{
				Table[bucket].Extract(i);
				found = true;
			}
		}
		if(Table[bucket][i]->key == key)
		{
			Table[bucket].Extract(i);
			found = true;
		}
	}
}

template< class K, class V >
V& tHTable< K, V >::Retrieve(K key)
{
	return getLocation(key)->value;
}

template< class K, class V >
V& tHTable< K, V >::operator[](K key)
{
	return getLocation(key)->value;
}

template< class K, class V >
void tHTable< K, V >::Update(K key, V value)
{
	getLocation(key)->value = value;
}

template< class K, class V >
tHNode< K, V >* tHTable< K, V >::getLocation(K key)
{
	int bucket( key % Table.getLength() );
	tHNode< K, V >* returnvalue;

	bool found(false);

	if( !(Table[bucket].isEmpty()) )
	{
		for(int i = 0; (Table[bucket][i] != Table[bucket].Last()) && (!found); i++)
		{
			if(Table[bucket][i]->key == key)
			{
				returnvalue = Table[bucket][i];
				found = true;
			}
		}
		if(Table[bucket][i]->key == key)
		{
			returnvalue = Table[bucket][i];
			found = true;
		}
	}

	if(!found)
	{
		throw EXCEPTION("tHNode< K, V >* tHTable< K, V >::getLocation(K key)^key not found^\n");
	}

	return returnvalue;
}

template< class K, class V >
void tHTable< K, V >::ReHash(int newsize)
{
	tLList< tHNode< K, V >* > temp;

	for(int i = 0; i < Table.getLength(); i++)
	{
		if( !(Table[i].isEmpty()) )
		{
			int j(0);
			for(j = 0; Table[i][j] != Table[i].Last(); j++)
			{
				temp.Append( new tHNode< K, V >(Table[i][j]->key, Table[i][j]->value) );
			}
			temp.Append( new tHNode< K, V >(Table[i][j]->key, Table[i][j]->value) );
			Table[i].Purge();
		}
	}

	Table.setLength(newsize);

	if( !(temp.isEmpty()) )
	{
		for(int i = 0; temp[i] != temp.Last(); i++)
		{
			Insert(temp[i]->key, temp[i]->value);
		}
		Insert(temp[i]->key, temp[i]->value);
	}
}

template< class K, class V >
void tHTable< K, V >::Enumerate()
{
	for(int i = 0; i < Table.getLength(); i++)
	{
		if( !(Table[i].isEmpty()) )
		{
			int j(0);
			cout<<i;
			for(j = 0; Table[i][j] != Table[i].Last(); j++)
			{
				cout<<" -> "<<Table[i][j]->key<<":"<<Table[i][j]->value;
			}
			cout<<" -> "<<Table[i][j]->key<<":"<<Table[i][j]->value;
			cout<<"\n";
		}
	}
}

template< class K, class V >
tHTable< K, V >::tHTable(const int& init_size)
:Table(init_size)
{
}

template< class K, class V >
tHTable< K, V >::~tHTable()
{
}

#endif