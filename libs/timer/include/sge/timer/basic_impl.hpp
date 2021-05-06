//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_BASIC_IMPL_HPP_INCLUDED
#define SGE_TIMER_BASIC_IMPL_HPP_INCLUDED

#include <sge/timer/basic_decl.hpp>
#include <sge/timer/parameters_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename Clock
>
sge::timer::basic<
	Clock
>::basic(
	parameters const &_params
)
:
	base(
		_params.clock()
	),
	interval_{
		_params.interval()
	},
	active_{
		_params.active()
	},
	expired_{
		_params.expired()
	},
	last_time_{
		this->now()
	}
{
}

FCPPT_PP_POP_WARNING

template<
	typename Clock
>
sge::timer::basic<
	Clock
>::basic(
	basic &&
)
noexcept
= default;

template<
	typename Clock
>
sge::timer::basic<
	Clock
> &
sge::timer::basic<
	Clock
>::operator=(
	basic &&
)
noexcept
= default;

namespace sge::timer
{
template<
	typename Clock
>
basic<
	Clock
>::~basic()
= default;
}

template<
	typename Clock
>
bool
sge::timer::basic<
	Clock
>::expired() const
{
	return
		active_
		&&
		(
			expired_
			||
			(
				this->now()
				-
				last_time_
			).count()
			>=
			interval_.count()
		);
}

template<
	typename Clock
>
void
sge::timer::basic<
	Clock
>::expired(
	bool const _expired
)
{
	expired_ =
		_expired;
}

template<
	typename Clock
>
bool
sge::timer::basic<
	Clock
>::active() const
{
	return
		active_;
}

template<
	typename Clock
>
void
sge::timer::basic<
	Clock
>::active(
	bool const _active
)
{
	if(
		active_
		==
		_active
	)
	{
		return;
	}

	if(
		active_
	)
	{
		active_ =
			false;
	}
	else
	{
		this->reset();

		active_ =
			true;
	}
}

template<
	typename Clock
>
typename
sge::timer::basic<
	Clock
>::duration
sge::timer::basic<
	Clock
>::interval() const
{
	return
		interval_;
}

template<
	typename Clock
>
void
sge::timer::basic<
	Clock
>::interval(
	duration const _interval
)
{
	interval_ =
		_interval;

	this->reset();
}

template<
	typename Clock
>
typename
sge::timer::basic<
	Clock
>::time_point
sge::timer::basic<
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
sge::timer::basic<
	Clock
>::time_point
sge::timer::basic<
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
sge::timer::basic<
	Clock
>::reset()
{
	last_time_ =
		this->now();

	expired_ =
		false;
}

#endif
