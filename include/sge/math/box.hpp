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


#ifndef SGE_MATH_BOX_HPP_INCLUDED
#define SGE_MATH_BOX_HPP_INCLUDED

namespace sge
{
namespace math
{

template<
	typename T
>
class box {
public:
	typedef T value_type;
	typedef T &reference;
	typedef T const &const_reference;

	box(
		const_reference left,
		const_reference top,
		const_reference right,
		const_reference bottom,
		const_reference front,
		const_reference back);

	value_type w() const;
	value_type h() const;
	value_type d() const;
	value_type volume() const;

	const_reference left() const;
	const_reference top() const;
	const_reference right() const;
	const_reference bottom() const;
	const_reference front() const;
	const_reference back() const;

	reference left();
	reference top();
	reference right();
	reference bottom();
	reference front();
	reference back();
private:
	value_type
		left_,
		top_,
		right_,
		bottom_,
		front_,
		back_;
};

template<
	typename T
>
bool operator==(
	box<T> const & l,
	box<T> const &r);

template<
	typename T
>
bool operator!=(
	box<T> const &l,
	box<T> const &r);

}

}

#endif
