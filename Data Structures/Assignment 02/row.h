#ifndef ROW_H
#define ROW_H

template<class T>
class Array2D;

template< class T >
class Row
{public:
	Row(Array2D< T >& array, int row);
	T& operator[](int column)const;
	Row< T > operator=(T& beMe);

private:
	Array2D< T >& m_array2D;
	int m_row;
};

template< class T >
Row< T >::Row(Array2D< T >& array, int row)
		 :m_array2D(array), m_row(row)
{
}

template< class T >
T& Row< T >::operator[](int column) const
{
	if(column > m_array2D.getColumns()) throw EXCEPTION("Array out of bounds: too high column\n");
	if(column < 0) throw EXCEPTION("Array out of bounds: too low column\n");
	return m_array2D.Select(m_row, column);
}

template< class T >
Row< T > Row< T >::operator=(T& beMe)
{
	m_array2D.Set(m_row, beMe);
}

#endif