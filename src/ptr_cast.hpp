/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PTR_CAST_HPP_INCLUDED
#define SGE_PTR_CAST_HPP_INCLUDED

#include <typeinfo>
#include <iostream>

namespace sge
{

template<typename T, typename U> inline T ptr_cast (const U u)
{
#ifndef SGE_FLAG_NORTTI
	if(!u)
		return 0;

	T t = dynamic_cast<T>(u);
	if(!t)
	{
		std::cerr << "ptr_cast: logic error, trying to cast from " << typeid(U).name() << " to " << typeid(T).name() << "!\n";
		throw std::bad_cast();
	}
	return t;
#else
	return static_cast<T>(u);
#endif
}

}

#endif
