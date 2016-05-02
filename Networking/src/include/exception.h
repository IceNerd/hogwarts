/***************************************************************************
Will Erickson
Copyright(c) 2005 PMSoft

02/28/2005

exception.h

Simple exception template
***************************************************************************/

/***************************************************************************
Pitchfork Engine
Copyright(c) 2005 PMSoft

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA."
***************************************************************************/

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

template <class T>
class Exception
{
	public:
		//constructor
		Exception(const T &value);

		//returns value
		T GetValue();
		//sets a value
		void SetValue(const T& value);

	protected:
		T tValue;
};

//constructor
template <class T>
Exception<T>::Exception(const T& value)
{
	this->tValue = value;
}

//returns value
template <class T>
T Exception<T>::GetValue()
{
	return this->tValue;
}

//changes value
template <class T>
	void Exception<T>::SetValue(const T& value)
{
	this->tValue = value;
}

#endif