//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/timer/parameters_decl.hpp>
#include <sge/timer/clocks/is_stateful.hpp>


// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
template<
	typename Clock
>
sge::timer::parameters<
	Clock
>::parameters(
	duration const _interval
)
:
	parameters(
		clock_type(),
		_interval
	)
{
	static_assert(
		!sge::timer::clocks::is_stateful<
			Clock
		>::value,
		"Stateful clocks need to be passed as parameters"
	);
}

template<
	typename Clock
>
sge::timer::parameters<
	Clock
>::parameters(
	clock_type const &_clock,
	duration const _interval
)
:
	state_base(
		_clock
	),
	interval_{
		_interval
	},
	active_{
		true
	},
	expired_{
		false
	}
{
}

template<
	typename Clock
>
sge::timer::parameters<
	Clock
> &
sge::timer::parameters<
	Clock
>::active(
	bool const _active
)
{
	active_ =
		_active;

	return
		*this;
}

template<
	typename Clock
>
sge::timer::parameters<
	Clock
> &
sge::timer::parameters<
	Clock
>::expired(
	bool const _expired
)
{
	expired_ =
		_expired;

	return
		*this;
}

template<
	typename Clock
>
typename
sge::timer::parameters<
	Clock
>::duration
sge::timer::parameters<
	Clock
>::interval() const
{
	return
		interval_;
}

template<
	typename Clock
>
typename
sge::timer::parameters<
	Clock
>::state_base const &
sge::timer::parameters<
	Clock
>::clock() const
{
	return
		*this;
}

template<
	typename Clock
>
bool
sge::timer::parameters<
	Clock
>::active() const
{
	return
		active_;
}

template<
	typename Clock
>
bool
sge::timer::parameters<
	Clock
>::expired() const
{
	return
		expired_;
}

#endif
