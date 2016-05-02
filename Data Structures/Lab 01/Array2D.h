/************************************************************************
* Class: Array2D
*
* Constructors:	
*	Array2D(int row, int column);
*		-rows set to row, columns set to column, m_array is sized
*			respectively.
*	Array2D(const Array2D< T >& copy);
*		-copy dictates the instantiation of the new object.  (copy)
*
* Mutators:
*	Array2D& operator=(const Array2D&);
*		-assigns one object to be of the same contents as another.
*	void Set(int who, T what);
*		-assigns array data member to be T
*	void SetColumns(int howMany);
*		-Resizes array to howMany columns
*	void SetRows(int howMany);
*		-Resizes array to howMany Rows
*
* Methods:		
*	int getLength() const;
*		-returns the length of the array
*	int getRows() const;
*		-returns how many rows are in the array'
*	int getColumns() const;
*		-returns how many columns are in the array
*	T& Select(int row, int column) const;
*		-returns the data in array[row][column]
*	Row< T > operator[](int row);
*		-returns a row
*************************************************************************/

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "row.h"
#include "error.h"

template< class T >
class Array2D
{public:
	Array2D(int row, int column);
	~Array2D();
	Array2D(const Array2D< T >& copy);

	//Mutators
	Array2D& operator=(const Array2D&);
	void Set(int who, T what);
	void SetColumns(int howMany);
	void SetRows(int howMany);

	//Other Methods
	int getLength() const
	{ return (m_rows * m_columns);}
	int getRows() const
	{ return m_rows;}
	int getColumns() const
	{ return m_columns;}
	T& Select(int row, int column) const;
	Row< T > operator[](int row);

	

protected:
	T** m_array;
	int m_rows;
	int m_columns;
};

/**************************************************************
*   Entry:  n/a
*
*    Exit:  Array2D on left side of op= will be a copy of the
*		one to the right.
*
* Purpose:  Canonical Function
*
***************************************************************/
template< class T >
Array2D< T >& Array2D< T >::operator=(const Array2D< T >& setTo)
{
	this->m_columns = setTo.m_columns;
	this->m_rows = setTo.m_rows;

	this->m_array = new T*[m_rows];
	for(int i = 0; i < this->m_rows; i++)
		this->m_array[i] = new T[this->m_columns];

	for(int i = 0; i < this->m_rows; i++)
	{
		for(int j = 0; j < this->m_columns; j++)
		{
			this->m_array[i][j] = setTo.Select(i, j);
		}
	}
	return *this;
}

/**************************************************************
*   Entry:  Who must be in the bounds of the array
*
*    Exit:  m_array[who] will be set to the given value
*
* Purpose:  be able to modify data
*
***************************************************************/
template< class T >
void Array2D< T >::Set(int who, T what)
{
	m_array[who] = what;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  Columns will be resized.  This leads to possible
*		loss of data, however, the user should take action to
*		save the data if it is important enough.
*
* Purpose:  Change the size of the array
*
***************************************************************/
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

/**************************************************************
*   Entry:  n/a
*
*    Exit:  Rows will be resized.  This leads to possible loss
*		of data, however, the user should take action to save
*		the data if it is important enough.
*
* Purpose:  Change the size of the array.
*
***************************************************************/
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

/**************************************************************
*   Entry:  row and column are within bounds of the array.
*
*    Exit:  data inside the array will be returned
*
* Purpose:  this is part of the sequence that results from the
*			double [] operation.
*
***************************************************************/
template< class T >
T& Array2D< T >::Select(int row, int column) const
{
	return m_array[row][column];
}

/**************************************************************
*   Entry:  row is within bounds of the array.
*
*    Exit:  A row will be returned, this allows for a double []
*			operation.
*
* Purpose:  first set of [] in the double [] operation
*
***************************************************************/
template< class T >
Row< T > Array2D< T >::operator[](int row)
{
	if(row > m_rows) throw EXCEPTION("Array out of bounds: too high row\n");
	if(row < 0) throw EXCEPTION("Array out of bounds:  too low row\n");
	return Row< T >(*this, row);
}



/**************************************************************
*   Entry:  row and column are positive ints
*
*    Exit:  Array2D object will be instantiated
*
* Purpose:  default constructor
*
***************************************************************/
template< class T >
Array2D< T >::Array2D(int row, int column)
			 :m_rows(row), m_columns(column)
{
	m_array = 0;
	m_array = new T*[row];
	for(int i = 0; i < row; i++)
		m_array[i] = new T[column];
}

/**************************************************************
*   Entry:  copy is an instantiated Array2D object
*
*    Exit:  copy will have been copied to the instantiating
*			object
*
* Purpose:  copy constructor
*
***************************************************************/
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

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  deconstructor
*
***************************************************************/
template< class T >
Array2D< T >::~Array2D()
{
	delete [] m_array;
}

#endif