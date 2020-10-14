//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_DELTA_IMPL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_DELTA_IMPL_HPP_INCLUDED

#include <sge/timer/clocks/delta_decl.hpp>


template<
	typename Duration
>
sge::timer::clocks::delta<
	Duration
>::delta()
:
	now_()
{
}

template<
	typename Duration
>
sge::timer::clocks::delta<
	Duration
>::~delta<
	Duration
>()
= default;

template<
	typename Duration
>
void
sge::timer::clocks::delta<
	Duration
>::update(
	duration const &_delta
)
{
	now_ +=
		_delta;
}

template<
	typename Duration
>
typename
sge::timer::clocks::delta<
	Duration
>::time_point
sge::timer::clocks::delta<
	Duration
>::now() const
{
	return
		now_;
}

#endif
