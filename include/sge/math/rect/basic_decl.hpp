/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MATH_RECT_BASIC_DECL_HPP_INCLUDED
#define SGE_MATH_RECT_BASIC_DECL_HPP_INCLUDED

#include <sge/math/rect/basic_fwd.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/dim/static.hpp>
#include <sge/math/size_type.hpp>
#include <boost/tr1/array.hpp>

namespace sge
{
namespace math
{
namespace rect
{

template<
	typename T
>
class basic {
public:
	typedef T value_type;
	
	typedef typename math::vector::static_<
		T,
		2
	>::type point_type;

	typedef typename math::dim::static_<
		T,
		2
	>::type dim_type;

	basic(
		value_type const &left,
		value_type const &top,
		value_type const &right,
		value_type const &bottom);

	basic(
		point_type const &pos,
		dim_type const &sz);

	static basic const null();

	value_type w() const;
	value_type h() const;

	point_type const pos() const;
	dim_type const dim() const;
	size_type area() const;

	value_type left() const;
	value_type top() const;
	value_type right() const;
	value_type bottom() const;

	void left(
		value_type);
	
	void top(
		value_type);
	
	void right(
		value_type);

	void bottom(
		value_type);
	
	// those are here because it is the same with vector, dim and matrix
	bool operator==(
		basic<T> const &) const;

	bool operator!=(
		basic const &) const;
private:
	void check_w() const;
	void check_h() const;
	void check() const;
	void throw_invalid() const;

	typedef std::tr1::array<
		T,
		4
	> internal_type;

	internal_type rep;
};

}
}
}

#endif
