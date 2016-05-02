/************************************************************************
* Class: tArray
*
* Constructors:	
*	tArray()
*
*
*	tArray(int length, int base=0)
*
*
*	tArray(const tArray&)
*
*
* Mutators:
*	tArray& operator=(const tArray&)
*
*
*	void setBase(int)
*
*
*	void setLength(int)
*
*
* Methods:
*	T& operator[](int) const
*
*
*	const T * getData() const
*
*
*	int getBase() const
*
*
*	int getLength() const
*
*	
*************************************************************************/

#ifndef TARRAY_H
#define TARRAY_H

template< class T >
class tArray
{ 	
public:
		tArray();
		~tArray();
		tArray(int length, int base=0);
		tArray(const tArray&);

		tArray& operator=(const tArray&); 
		T& operator[](int) const;
		const T * getData() const;
		int getBase() const;
		int getLength() const;
		void setBase(int);
		void setLength(int);
   	protected:
		T* m_data;
		int m_base;
		int m_length;
};

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tArray< T >& tArray< T >::operator=(const tArray& array)
{
	m_data = new T[array.getLength()];
	m_base = array.getBase();
	m_length = array.getLength();
	for(int i = 0; i < m_length; i++)
	{
		m_data[i] = array[i];
	}
	return *this;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
T& tArray< T >::operator[](int index) const
{
	if(index >= m_base + m_length) throw EXCEPTION("Array out of bounds! -- Too High\n");
	if(index < m_base) throw EXCEPTION("Array out of bounds! -- Too Low\n");
	return m_data[index - m_base];
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
int tArray< T >::getBase() const
{
	return m_base;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
const T* tArray< T >::getData() const
{
	return m_data;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
int tArray< T >::getLength() const
{
	return m_length;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
void tArray< T >::setBase(int newBase)
{
	m_base = newBase;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
void tArray< T >::setLength(int newLength)
{
	T* temp;
	int limit(0);

	temp = new T[m_length];
	for(int i = 0; i < m_length; i++)
		temp[i] = m_data[i];
	if(newLength > m_length)
		limit = m_length;
	else
		limit = newLength;

	delete [] m_data;
	m_data = new T[newLength];
	for(int i = 0; i < limit; i++)
		m_data[i] = temp[i];
	m_length = newLength;
}

//-----------CTORS / DTORS

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tArray< T >::tArray()
		   :m_data(0), m_base(0), m_length(0)
{
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tArray< T >::tArray(int length, int base)
		   :m_length(length), m_base(base)
{
	m_data = new T[length];
	//for(int i = 0; i < length; i ++)
	//	m_data[i] = NULL;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tArray< T >::tArray(const tArray& copy)
		   :m_base(copy.getBase()), m_length(copy.getLength())
{
	m_data = new T[m_length];
	for(int i = 0; i < m_length; i++)
		m_data[i] = copy[i];
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
template< class T >
tArray< T >::~tArray()
{
	delete [] m_data;
}

#endif