//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
[[nodiscard]]
bool
impl(
	fcppt::math::vector::object<
		T,
		2,
		S1
	> const &_start,
	fcppt::math::vector::object<
		T,
		2,
		S2
	> const &_end,
	Callback const &_callback
)
{
	static_assert(
		std::is_signed_v<
			T
		>,
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

	using
	vector_type
	=
	fcppt::math::vector::static_<
		T,
		2
	>;

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
		{
			return
				false;
		}

		if(
			x0 == x1
			&&
			y0 == y1
		)
		{
			break;
		}

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
			{
				return
					false;
			}
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
			{
				return
					false;
			}

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
			{
				return
					false;
			}
		}
	}

	return
		true;
}

}
}
}

#endif
