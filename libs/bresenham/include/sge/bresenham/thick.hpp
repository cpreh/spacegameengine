/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_BRESENHAM_THICK_HPP_INCLUDED
#define SGE_BRESENHAM_THICK_HPP_INCLUDED

#include <sge/bresenham/detail/impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bresenham
{

/**
\brief Thick version of the bresenham algorithm

Plots points using bresenham between \a _start and \a _end. For each point in
the set, \a _callback is called. If \a _callback returns <code>false</code>
the algorithm stops.

\tparam Callback A function callable as <code>bool (fcppt::math::vector::static_<T,2>)</code>

\return <code>true</code> iff every call to \a _callback returns <code>true</code>
*/
template<
	typename T,
	typename S1,
	typename S2,
	typename Callback
>
inline
bool
thick(
	fcppt::math::vector::object<
		T,
		2,
		S1
	> const _start,
	fcppt::math::vector::object<
		T,
		2,
		S2
	> const _end,
	Callback const &_callback
)
{
	return
		sge::bresenham::detail::impl<
			true
		>(
			_start,
			_end,
			_callback
		);
}

}
}

#endif
