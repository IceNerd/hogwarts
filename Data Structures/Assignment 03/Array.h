#ifndef ARRAY_H
#define ARRAY_H

template< class T >
class Array
{ 	
public:
		Array();
		~Array();
		Array(int length, int base=0);
		Array(const Array & copy);

		Array& operator=(const Array & array); 
		T& operator[](int index) const;
		const T * getData() const;
		int getBase() const;
		int getLength() const;
		void setBase(int newBase);
		void setLength(int newLength);
   	protected:
		T* m_data;
		int m_base;
		int m_length;
};

template< class T >
Array< T >& Array< T >::operator=(const Array& array)
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

template< class T >
T& Array< T >::operator[](int index) const
{
	if(index >= m_base + m_length) throw EXCEPTION("Array out of bounds! -- Too High\n");
	if(index < m_base) throw EXCEPTION("Array out of bounds! -- Too Low\n");
	return m_data[index - m_base];
}

template< class T >
int Array< T >::getBase() const
{
	return m_base;
}

template< class T >
const T* Array< T >::getData() const
{
	return m_data;
}

template< class T >
int Array< T >::getLength() const
{
	return m_length;
}

template< class T >
void Array< T >::setBase(int newBase)
{
	m_base = newBase;
}

template< class T >
void Array< T >::setLength(int newLength)
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
template< class T >
Array< T >::Array()
		   :m_data(0), m_base(0), m_length(0)
{
}

template< class T >
Array< T >::Array(int length, int base)
		   :m_length(length), m_base(base)
{
	m_data = new T[length];
	//for(int i = 0; i < length; i ++)
	//	m_data[i] = NULL;
}

template< class T >
Array< T >::Array(const Array& copy)
		   :m_base(copy.getBase()), m_length(copy.getLength())
{
	m_data = new T[m_length];
	for(int i = 0; i < m_length; i++)
		m_data[i] = copy[i];
}

template< class T >
Array< T >::~Array()
{
	cout<<"Destroying Array\n";
	delete [] m_data;
}

#endif