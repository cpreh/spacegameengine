//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_DIFFERENCE_HPP_INCLUDED
#define SGE_TIMER_DIFFERENCE_HPP_INCLUDED


namespace sge::timer
{

template<
	typename Timer
>
inline
typename
Timer::duration
difference(
	Timer const &_timer
)
{
	return
		_timer.now()
		-
		_timer.last_time();
}

}

#endif
