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


#ifndef SGE_MATH_RECT_HPP_INCLUDED
#define SGE_MATH_RECT_HPP_INCLUDED

#include <iosfwd>
#include "dim.hpp"
#include "vector.hpp"

namespace sge
{
namespace math 
{
template<typename T> class basic_rect {
public:
	typedef T                       value_type;
	typedef T&                      reference;
	typedef const T&                const_reference;
	typedef math::basic_vector<T,2> point_type;
	typedef math::basic_dim<T,2>    dim_type;

	basic_rect(const value_type& left   = value_type(),
	           const value_type& top    = value_type(),
	           const value_type& right  = value_type(),
	           const value_type& bottom = value_type());

	basic_rect(const point_type& pos, const dim_type& sz);

	value_type w() const;
	value_type h() const;

	point_type pos() const;
	dim_type size() const;

	const_reference left() const;
	const_reference top() const;
	const_reference right() const;
	const_reference bottom() const;

	reference left();
	reference top();
	reference right();
	reference bottom();
private:
	value_type left_,
	           top_,
	           right_,
	           bottom_;
};

template<typename T>
basic_rect<T> operator+(const basic_rect<T>& l,
                        const typename basic_rect<T>::point_type& r);

template<typename T>
basic_rect<T> operator-(const basic_rect<T>& l,
                        const typename basic_rect<T>::point_type& r);

template<typename T>
bool operator==(const basic_rect<T>& l, const basic_rect<T>& r);

template<typename T>
bool operator!=(const basic_rect<T>& l, const basic_rect<T>& r);

template<typename T>
basic_rect<T> resize_borders(const basic_rect<T>& r, const T diff);

template<typename T, typename Ch, typename Traits>
std::basic_ostream<Ch,Traits>& operator<<(std::basic_ostream<Ch,Traits>& s,
                                          const basic_rect<T>& r);

template<typename D, typename S>
basic_rect<D> structure_cast(const basic_rect<S>& r);

typedef basic_rect<space_unit> rect;

}
}

#endif
