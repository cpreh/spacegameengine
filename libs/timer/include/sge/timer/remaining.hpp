//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_REMAINING_HPP_INCLUDED
#define SGE_TIMER_REMAINING_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed.hpp>


namespace sge
{
namespace timer
{

template<
	typename Clock
>
typename
Clock::duration
remaining(
	sge::timer::basic<
		Clock
	> const &_timer
)
{
	return
		_timer.interval()
		-
		sge::timer::elapsed(
			_timer
		);
}

}
}

#endif
