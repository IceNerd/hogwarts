/*************************************************************************
Alberto Martinez
04/10/2005

property.h

Property template to combine simple getter AND setter functions
**************************************************************************/
#ifndef PROPERTY_H
#define PROPERTY_H

	template <class T>
	class Property
	{
		public:
			//--- Constructor --------------------------------------------
			Property( T* value );

			//--- Public -------------------------------------------------
			operator T();
			T operator =( const T& value );

		private:
			T* data;
	};

//--- Constructor --------------------------------------------------------
	template <class T>
	Property<T>::Property( T* value )
	{
		this->data = value;
	}

//--- Public -------------------------------------------------------------
	//Operator T
	template <class T>
	Property<T>::operator T()
	{
		return (*this->data);
	}

	//Operator =
	template <class T>
	T Property<T>::operator =( const T& value )
	{
		(*this->data) = value;
		return (*this->data);
	}

#endif