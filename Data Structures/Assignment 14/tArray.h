/************************************************************************
* Class: tArray
*
* Constructors:	
*	tArray()
*	tArray(int length, int base=0)
*	tArray(const tArray&)
*
*
* Mutators:
*
* Methods:
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
		T& operator[](int);
		const T * getData() const;
		int getBase() const;
		int getLength() const;
		void setBase(int);
		void setLength(int);

		//sorts
		void Sort_Bubble();
		void Sort_F_Bubble();
		void Sort_Selection();
		void Sort_Insertion();
		void Sort_Shell();
		void Sort_Heap();
		void Sort_Merge();
		void Sort_Quick();

   	protected:
		void MoveDown(int, int);
		void MergeSort(tArray< T >&, int, int);
		void Merge(tArray< T >&, int, int, int);
		void QuickSort(int, int);

		T* m_data;
		int m_base;
		int m_length;
};

template< class T >
void tArray< T >::Sort_Bubble()
{
	T tempCont;
	for(int i = 0; i < m_length; i++)
	{
		for(int j = 0; j < m_length-1; j++)
		{
			if(m_data[j] > m_data[j+1])
			{
				tempCont = m_data[j];
				m_data[j] = m_data[j+1];
				m_data[j+1] = tempCont;
			}
		}
	}
}

template< class T >
void tArray< T >::Sort_F_Bubble()
{
	T tempCont;
	bool sorted(false);

	for(int i = 0; (i < m_length) && (sorted == false); i++)
	{
		sorted = true;
		for(int j = 0; j < m_length - i - 1; j++)
		{
			if(m_data[j] > m_data[j+1])
			{
				sorted = false;
				tempCont = m_data[j];
				m_data[j] = m_data[j+1];
				m_data[j+1] = tempCont;
			}
		}
	}
}

template< class T >
void tArray< T >::Sort_Selection()
{
	int swap(0);
	T swap_cont;

	for(int i = 0; i < m_length; i++)
	{
		swap = i;
		for(int j = i; j < m_length; j++)
		{
			if(m_data[j] < m_data[swap])
			{
				swap = j;
			}
		}
		swap_cont = m_data[i];
		m_data[i] = m_data[swap];
		m_data[swap] = swap_cont;
	}
}

template< class T >
void tArray<  T>::Sort_Insertion()
{
	T swap_cont;

	for(int i = 1; i < m_length; i++)
	{
		swap_cont = m_data[i];
		int j(i);
		for(j = i; (j > 0) && (swap_cont < m_data[j - 1]); j--)
		{
			m_data[j] = m_data[j - 1];
		}
		m_data[j] = swap_cont;
	}
}

template< class T >
void tArray< T >::Sort_Shell()
{
	int h(1);
	while(h < m_length)
	{
		for(int hCnt = h; hCnt < 2 * h; hCnt++)
		{
			//Insertion Sort
			T tmp;
			
			for(int j = hCnt; j < m_length; j += h)
			{
				tmp = m_data[j];
				int k(j);
				while( (k - h >= 0) && (tmp < m_data[k-h]) )
				{
					m_data[k] = m_data[k-h];
					k = k - h;
				}
				m_data[k] = tmp;
			}
		}
		h = 3 * h +1;
	}
}

template< class T >
void tArray< T >::Sort_Heap()
{
	for(int i = (m_length/2); i >= 0; i--)
	{
		MoveDown(i, m_length);
	}

	for(int i = m_length-1; i != 0; i--)
	{
		//cout<<i<<"\n";
		T temp;

		temp = m_data[0];
		m_data[0] = m_data[i];
		m_data[i] = temp;

		MoveDown(0, i - 1);
	}
}

template< class T >
void tArray< T >::MoveDown(int first, int last)
{
	int Largest( first * 2 + 1 );

	while( !(Largest > last) )
	{
		if( (Largest < last) && (m_data[Largest] < m_data[Largest+1]) )
		{
			Largest++;
		}

		if( m_data[first] < m_data[Largest] )
		{
			//swap
			T temp(m_data[first]);
			m_data[first] = m_data[Largest];
			m_data[Largest] = temp;

			first = Largest;
			Largest = first * 2 + 1;
		}
		else
		{
			Largest = last+1;
		}
	}
}

template< class T >
void tArray< T >::Sort_Merge()
{
	tArray< T > temp(m_length);
	for(int i = 0; i < m_length; i++)
	{
		temp[i] = m_data[i];
	}

	MergeSort(temp, 0, m_length-1);
}

template< class T >
void tArray< T >::MergeSort(tArray< T >& temp, int left, int right)
{
	if(left < right)
	{
		int mid( (left + right)/2 );
		MergeSort(temp, left, mid);
		MergeSort(temp, mid+1, right);
		Merge(temp, left, mid+1, right);
	}
}

template< class T >
void tArray< T >::Merge(tArray< T >& temp, int arg1, int arg2, int rightend)
{
	int left(arg1);
	int right(arg2);
	int left_end(right - 1);
	int temp_pos(left);
	int num_elements(rightend - left);

	while( (left <= left_end) && (right <= rightend) )
	{
		if( m_data[left] <= m_data[right] )
		{
			temp[temp_pos] = m_data[left];
			temp_pos++;
			left++;
		}
		else
		{
			temp[temp_pos] = m_data[right];
			temp_pos++;
			right++;
		}
	}


		while( left <= left_end )
		{
			temp[temp_pos] = m_data[left];
			temp_pos++;
			left++;
		}

	

		while( right <= rightend )
		{
			temp[temp_pos] = m_data[right];
			temp_pos++;
			right++;
		}

	for(int i = arg1; i < rightend + 1; i++)
	{
		m_data[i] = temp[i];
	}
}

template< class T >
void tArray< T >::Sort_Quick()
{
	int max(0);
	if( m_length >= 2 )
	{
		for(int i = 1; i < m_length; i++)
		{
			if(m_data[max] < m_data[i])
			{
				max = i;
			}
		}
		T temp(m_data[max]);
		m_data[max] = m_data[m_length - 1];
		m_data[m_length - 1] = temp;
		QuickSort(0, m_length - 2);
	}
}

template< class T >
void tArray< T >::QuickSort(int first, int last)
{
	int small(first + 1);
	int large(last);
	T pivot(m_data[first]);

	while(small <= large)
	{
		while(m_data[small] < pivot)
			small++;
		while(m_data[large] > pivot)
			large--;
		if(small < large)
		{
			T temp(m_data[small]);
			m_data[small] = m_data[large];
			m_data[large] = temp;

			small++;
			large--;
		}
		else
		{
			small++;
		}
	}
	T temp2(m_data[large]);
	m_data[large] = m_data[first];
	m_data[first] = temp2;
	if(first < large - 1)
		QuickSort(first, large - 1);
	if(last > large + 1)
		QuickSort(large + 1, last);
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
T& tArray< T >::operator[](int index)
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