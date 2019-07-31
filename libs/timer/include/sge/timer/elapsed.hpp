//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_ELAPSED_HPP_INCLUDED
#define SGE_TIMER_ELAPSED_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <sge/timer/difference.hpp>


namespace sge
{
namespace timer
{

template<
	typename Clock
>
typename
Clock::duration
elapsed(
	sge::timer::basic<
		Clock
	> const &_timer
)
{
	if(
		!_timer.active()
	)
		return
			typename
			Clock::duration{};

	if(
		_timer.expired()
	)
		return
			_timer.interval();

	return
		sge::timer::difference(
			_timer
		);
}

}
}

#endif
