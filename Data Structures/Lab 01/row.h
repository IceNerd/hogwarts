/************************************************************************
* Class: row
*
* Constructors:	
*	Row(Array2D< T >& array, int row);
*		-m_row set to row, m_array2D is set to array
*
* Mutators:
*	Row< T > operator=(T& beMe);
*		-sets a data member
*
* Methods:
*	T& operator[](int column)const;	
*		-part 2 of double [] operation to return a data member.
*************************************************************************/

#ifndef ROW_H
#define ROW_H

template< class T >
class Array2D;

template< class T >
class Row
{public:
	Row(Array2D< T >& array, int row);

	//Mutators
	Row< T > operator=(T& beMe);

	//Other Methods
	T& operator[](int column)const;

private:
	Array2D< T >& m_array2D;
	int m_row;
};

/**************************************************************
*   Entry:  columns is within the bounds of the array
*
*    Exit:  returns the data member of row, column of the array
*
* Purpose:  to retrieve data
*
***************************************************************/
template< class T >
T& Row< T >::operator[](int column) const
{
	if(column > m_array2D.getColumns()) throw EXCEPTION("Array out of bounds: too high column\n");
	if(column < 0) throw EXCEPTION("Array out of bounds: too low column\n");
	return m_array2D.Select(m_row, column);
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  m_array2D data member is set to a value
*
* Purpose:  
*
***************************************************************/
template< class T >
Row< T > Row< T >::operator=(T& beMe)
{
	m_array2D.Set(m_row, beMe);
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  data is initialized
*
* Purpose:  default constructor
*
***************************************************************/
template< class T >
Row< T >::Row(Array2D< T >& array, int row)
		 :m_array2D(array), m_row(row)
{
}

#endif