//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_RESET_WHEN_EXPIRED_HPP_INCLUDED
#define SGE_TIMER_RESET_WHEN_EXPIRED_HPP_INCLUDED

#include <sge/timer/basic.hpp>


namespace sge
{
namespace timer
{

template<
	typename Clock
>
bool
reset_when_expired(
	sge::timer::basic<
		Clock
	> &_timer
)
{
	if(
		!_timer.expired()
	)
		return
			false;

	_timer.reset();

	return
		true;
}

}
}

#endif
