//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_REMAINING_FRACTIONAL_HPP_INCLUDED
#define SGE_TIMER_REMAINING_FRACTIONAL_HPP_INCLUDED

#include <sge/timer/basic_fwd.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{

template<
	typename Float,
	typename Clock
>
Float
remaining_fractional(
	sge::timer::basic<
		Clock
	> const &_timer
)
{
	static_assert(
		std::is_floating_point<
			Float
		>::value,
		"Float must be a floating point type"
	);

	return
		fcppt::literal<
			Float
		>(
			1
		)
		-
		sge::timer::elapsed_fractional<
			Float
		>(
			_timer
		);
}

}
}

#endif
