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


#ifndef SGE_MATH_CIRCLE_HPP_INCLUDED
#define SGE_MATH_CIRCLE_HPP_INCLUDED

#include <sge/math/circle_fwd.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sge
{
namespace math
{

/**
 * \attention To use circle's functions you have to include
 * <sge/math/circle_impl.hpp>!
 */
template<
	typename T
>
class circle {
public:
	typedef T value_type;
	typedef T &reference;
	typedef T const &const_reference;
	typedef typename vector::static_<
		value_type,
		2
	>::type point_type;

	circle(
		const_reference x,
		const_reference y,
		const_reference radius);

	circle(
		const point_type& origin,
		const_reference radius);

	point_type& origin();
	const point_type& origin() const;
	reference radius();
	const_reference radius() const;
private:
	point_type origin_;
	value_type radius_;
};

template<typename T>
bool intersects(
	circle<T> const&,
	circle<T> const&);

}
}

#endif
