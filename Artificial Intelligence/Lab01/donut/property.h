#ifndef __PROPERTY_H__
#define __PROPERTY_H__

template <class T>
class Property
{
	public:
		//constructor
		Property(T* value);

		//allows class to be passed off as the data it contains
		operator T();

		//modifies the stored data
		T operator =(const T& value);

	private:
		T* data;
};

//constructor
template <class T>
Property<T>::Property(T* value)
{
	this->data = value;
}

//allows class to be passed of as the data it contains
template <class T>
Property<T>::operator T()
{
	return *(this->data);
}

//modifies the stored data
template <class T>
T Property<T>::operator =(const T& value)
{
	*(this->data) = value;
	return *(this->data);
}

#endif