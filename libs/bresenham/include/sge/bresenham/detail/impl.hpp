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


#ifndef SGE_BRESENHAM_DETAIL_IMPL_HPP_INCLUDED
#define SGE_BRESENHAM_DETAIL_IMPL_HPP_INCLUDED

#include <sge/bresenham/detail/thick.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bresenham
{
namespace detail
{

template<
	bool Thick,
	typename T,
	typename S1,
	typename S2,
	typename Callback
>
bool
impl(
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
	static_assert(
		std::is_signed<
			T
		>::value,
		"bresenham currently only works on signed types"
	);

	T x0(
		_start.x()
	);

	T y0(
		_start.y()
	);

	T x1(
		_end.x()
	);

	T y1(
		_end.y()
	);

	T const two(
		fcppt::literal<
			T
		>(
			2
		)
	);

	T const one(
		fcppt::literal<
			T
		>(
			1
		)
	);

	T const dx(
		fcppt::math::diff(
			x1,
			x0
		)
	);

	T const dy(
		fcppt::math::diff(
			y1,
			y0
		)
	);

	T const sx{
		x0 < x1
		?
			one
		:
			-one
	};

	T const sy{
		y0 < y1
		?
			one
		:
			-one
	};

	T err{
		dx
		-
		dy
	};

	typedef
	fcppt::math::vector::static_<
		T,
		2
	>
	vector_type;

	auto const plot(
		[
			&_callback
		](
			T const &_x,
			T const &_y
		)
		-> bool
		{
				return
					_callback(
						vector_type(
							_x,
							_y
						)
					);
		}
	);

	while(
		true
	)
	{
		if(
			!plot(
				x0,
				y0
			)
		)
			return
				false;

		if(
			x0 == x1
			&&
			y0 == y1
		)
			break;

		T const err2{
			two * err
		};

		if(
			err2
			>
			-dy
		)
		{
			err -=
				dy;

			x0 +=
				sx;

			if(
				!sge::bresenham::detail::thick<
					Thick
				>(
					plot,
					x0 - sx,
					y0
				)
			)
				return
					false;
		}

		if(
			x0 == x1
			&&
			y0 == y1
		)
		{
			if(
				!plot(
					x0,
					y0
				)
			)
				return
					false;
			break;
		}

		if(
			err2
			<
			dx
		)
		{
			err +=
				dx;

			y0 +=
				sy;

			if(
				!sge::bresenham::detail::thick<
					Thick
				>(
					plot,
					x0,
					y0 - sy
				)
			)
				return
					false;
		}
	}

	return
		true;
}

}
}
}

#endif
