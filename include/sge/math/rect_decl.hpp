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



#ifndef SGE_MATH_RECT_DECL_HPP_INCLUDED
#define SGE_MATH_RECT_DECL_HPP_INCLUDED

#include <sge/math/dim/static.hpp>
#include <sge/math/vector/static.hpp>
#include <iosfwd>
#include <cstddef>

namespace sge
{
namespace math 
{
/**
 * \attention To use rect's functions you have to include <sge/math/rect_impl.hpp>!
 */
template<
	typename T
>
class rect {
public:
	typedef T value_type;
	typedef std::size_t size_type;
	typedef T &reference;
	typedef T const &const_reference;

	typedef typename math::vector::static_<
		T,
		2
	>::type point_type;
	typedef typename math::dim::static_<
		T,
		2
	>::type dim_type;

	/**
	 * Default constructs all parameters which are not given(sets them to zero
	 * for arithmetic built-in types)
	 * \throw sge::exception If right is smaller than left or bottom is smaller than top
	 */
	explicit rect(
		value_type const &left   = value_type(),
		value_type const &top    = value_type(),
		value_type const &right  = value_type(),
		value_type const &bottom = value_type());

	/**
	 * \throw sge::exception If right is smaller than left or bottom is smaller than top
	 */
	rect(
		point_type const &pos,
		dim_type const &sz);

	/**
	 * Same as <tt>rect(point_type(0,0),sz)</tt>
	 */
	explicit rect(
		dim_type const &sz);
	
	static rect const null();

	value_type w() const;
	value_type h() const;

	point_type const pos() const;
	dim_type const dim() const;
	size_type area() const;

	const_reference left() const;
	const_reference top() const;
	const_reference right() const;
	const_reference bottom() const;

	reference left();
	reference top();
	reference right();
	reference bottom();
private:
	void check();

	value_type left_,
	           top_,
	           right_,
	           bottom_;
};

template<typename T>
rect<T> const operator+(
	const rect<T>& l,
	const typename rect<T>::point_type& r);

template<typename T>
rect<T> const operator-(
	const rect<T>& l,
	const typename rect<T>::point_type& r);

/**
 * Uses sge::math::compare to compare the components
 */
template<typename T>
bool operator==(const rect<T>& l, const rect<T>& r);

/**
 * Uses sge::math::compare to compare the components
 */
template<typename T>
bool operator!=(const rect<T>& l, const rect<T>& r);

/**
 * Resizes the rect and adds a border of \c diff at each side
 */
template<typename T>
rect<T> const resize_borders(const rect<T>& r, const T diff);

template<typename T, typename Ch, typename Traits>
std::basic_ostream<Ch,Traits>& operator<<(std::basic_ostream<Ch,Traits>& s,
                                          const rect<T>& r);

template<
	typename D,
	typename S
>
D const
structure_cast(
	rect<S> const &);

}
}

#endif
