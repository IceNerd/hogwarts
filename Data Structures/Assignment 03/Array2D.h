#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "row.h"

template< class T >
class Array2D
{public:
	Array2D(int row, int column);
	~Array2D();
	Array2D(const Array2D< T >& copy);
	Array2D& operator=(const Array2D&);
	T& Select(int row, int column) const;
	Row< T > operator[](int row);

	int getLength() const
	{ return (m_rows * m_columns);}
	int getRows() const
	{ return m_rows;}
	int getColumns() const
	{ return m_columns;}

	//mutators
	void Set(int who, T what);
	void SetColumns(int howMany);
	void SetRows(int howMany);

protected:
	T** m_array;
	int m_rows;
	int m_columns;
};

template< class T >
Array2D< T >::Array2D(int row, int column)
			 :m_rows(row), m_columns(column)
{
	m_array = new T*[row];
	for(int i = 0; i < row; i++)
		m_array[i] = new T[column];
}

template< class T >
Array2D< T >::~Array2D()
{
	delete [] m_array;
}

template< class T >
Array2D< T >::Array2D(const Array2D< T >& copy)
			 :m_columns(copy.getColumns()), m_rows(copy.getRows())
{
	m_array = new T*[m_rows];
	for(int i = 0; i < m_rows; i++)
		m_array[i] = new T[m_columns];

	for(int i = 0; i < m_rows; i++)
	{
		for(int j = 0; j < m_columns; j++)
		{
			m_array[i][j] = copy.Select(i, j);
		}
	}
}

template< class T >
Array2D< T >& Array2D< T >::operator=(const Array2D< T >& setTo)
{
	this->m_array = setTo.m_array;
	this->m_columns = setTo.m_columns;
	this->m_rows = setTo.m_rows;
	return *this;
}

template< class T >
T& Array2D< T >::Select(int row, int column) const
{
	return m_array[row][column];
}

template< class T >
Row< T > Array2D< T >::operator[](int row)
{
	if(row > m_rows) throw EXCEPTION("Array out of bounds: too high row\n");
	if(row < 0) throw EXCEPTION("Array out of bounds:  too low row\n");
	return Row< T >(*this, row);
}

template< class T >
void Array2D< T >::Set(int who, T what)
{
	m_array[who] = what;
}

template< class T >
void Array2D< T >::SetColumns(int howMany)
{
	T** temp_array;
	temp_array = new T*[m_rows];
	for(int i = 0; i < m_rows; i++)
		temp_array[i] = new T[m_columns];

	for(int i = 0; i < (m_rows); i++)
	{
		for(int j = 0; j < (m_columns); j++)
		{
		temp_array[i] = m_array[i];
		}
	}

	m_array = new T*[m_rows];
	for(int i = 0; i < m_rows; i++)
		m_array[i] = new T[howMany]; //new length set

	for(int i = 0; i < m_rows; i++)
	{
		for(int j = 0; (j < howMany) && (j < m_columns); j++)
		{
			m_array[i][j] = temp_array[i][j];
		}
	}
	m_columns = howMany;
}

template< class T >
void Array2D< T >::SetRows(int howMany)
{
	T** temp_array;
	temp_array = new T*[m_rows];
	for(int i = 0; i < m_rows; i++)
		temp_array[i] = new T[m_columns];

	for(int i = 0; i < (m_rows); i++)
	{
		for(int j = 0; j < (m_columns); j++)
		{
		temp_array[i] = m_array[i];
		}
	}

	m_array = new T*[howMany];
	for(int i = 0; i < howMany; i++)
		m_array[i] = new T[m_columns]; //new length set //new length set

	for(int i = 0; (i < howMany) && (i < m_rows); i++)
	{
		for(int j = 0; j < m_columns; j++)
		{
			m_array[i][j] = temp_array[i][j];
		}
	}
	m_rows = howMany;
}

#endif