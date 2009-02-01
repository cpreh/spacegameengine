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


#ifndef SGE_ARRAY_WRAPPER_HPP_INCLUDED
#define SGE_ARRAY_WRAPPER_HPP_INCLUDED

#include <cstddef>

namespace sge
{

template<
	typename T
>
class array_wrapper {
public:
	typedef std::size_t size_type;
	typedef T value_type;
	typedef T &reference;
	typedef T *pointer;
	typedef pointer iterator;

	array_wrapper(
		pointer first,
		pointer last);
	
	array_wrapper(
		pointer first,
		size_type sz);

	iterator begin() const;
	iterator end() const;
	pointer data() const;
	pointer data_end() const;
	size_type size() const;

	bool empty() const;
private:
	pointer
		first,
		last;
};

}

#endif
