/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_X_RESOURCE_HPP_INCLUDED
#define SGE_X_RESOURCE_HPP_INCLUDED

#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <X11/Xlib.h>

namespace sge
{

template<typename T>
struct x_resource : boost::noncopyable {
	x_resource()
	: t(0)
	{}
	
	x_resource(const T t)
	: t(t)
	{}

	~x_resource()
	{
		if(t)
			XFree(t);
	}
	
	x_resource& operator=(const T& _t)
	{
		t = _t;
		return *this;
	}

	const T& operator->() const { return t; }
	const T& operator*() const { return t; }
	const T* pointer_to() const { return &t; }
	T get() { return t; }
	T* pointer_to() { return &t; }
private:
	T t;
};

}

#endif
