//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_ABSOLUTE_IMPL_HPP_INCLUDED
#define SGE_TIMER_ABSOLUTE_IMPL_HPP_INCLUDED

#include <sge/timer/absolute_decl.hpp>
#include <sge/timer/clocks/is_stateful.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


template<
	typename Clock
>
sge::timer::absolute<
	Clock
>::absolute()
:
	absolute(
		clock_parameter{}
	)
{
	static_assert(
		!sge::timer::clocks::is_stateful<
			Clock
		>::value
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename Clock
>
sge::timer::absolute<
	Clock
>::absolute(
	clock_parameter const _clock
)
:
	base(
		_clock
	),
	last_time_{
		this->now()
	}
{
}

FCPPT_PP_POP_WARNING

template<
	typename Clock
>
typename
sge::timer::absolute<
	Clock
>::time_point
sge::timer::absolute<
	Clock
>::now() const
{
	return
		this->clock_base().now();
}

template<
	typename Clock
>
typename
sge::timer::absolute<
	Clock
>::time_point
sge::timer::absolute<
	Clock
>::last_time() const
{
	return
		last_time_;
}

template<
	typename Clock
>
void
sge::timer::absolute<
	Clock
>::reset()
{
	last_time_ =
		this->now();
}

#endif
