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


#ifndef SGE_MATRIX_PROXY_HPP_INCLUDED
#define SGE_MATRIX_PROXY_HPP_INCLUDED

#include <cstddef>

namespace sge
{
namespace detail
{

template<typename Reference, typename Pointer, std::size_t Stride>
class matrix_proxy_impl {
public:
	typedef std::size_t size_type;
	Reference operator[](const size_type y) const { return p[y*Stride + x]; }
	matrix_proxy_impl(size_type x, const Pointer p) : x(x), p(p) {}
private:
	const size_type x;
	const Pointer p;

	matrix_proxy_impl& operator=(const matrix_proxy_impl&);
};
}

}

#endif
