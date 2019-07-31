//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TIMER_CLOCKS_ADJUSTABLE_IMPL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_ADJUSTABLE_IMPL_HPP_INCLUDED

#include <sge/timer/clocks/adjustable_decl.hpp>


template<typename ClockImpl>
sge::timer::clocks::adjustable<ClockImpl>::adjustable()
:
	current_time_(
		ClockImpl::now()),
	transformed_time_(
		current_time_),
	factor_(
		1.0f)
{
}

template<typename ClockImpl>
sge::timer::clocks::adjustable<ClockImpl>::~adjustable()
{
}

template<typename ClockImpl>
void
sge::timer::clocks::adjustable<ClockImpl>::update()
{
	// So what does this do? Well, we effectively manage two "clocks"
	// here. One goes along with the real clock (with
	// sge::timer::clock) and knows the "real" current time. The other
	// one (transformed_time) might be faster or slower than the real
	// clock. The real clock acts as a "duration difference" giver.
	time_point const latest_time =
		ClockImpl::now();

	duration const diff(
		static_cast<rep>(
			factor_ *
			static_cast<float_type>(
				(latest_time - current_time_).count())));

	transformed_time_ +=
		diff;

	current_time_ =
		latest_time;
}

template<typename ClockImpl>
typename
sge::timer::clocks::adjustable<ClockImpl>::float_type
sge::timer::clocks::adjustable<ClockImpl>::factor() const
{
	return factor_;
}

template<typename ClockImpl>
void
sge::timer::clocks::adjustable<ClockImpl>::factor(
	float_type const _factor)
{
	factor_ =
		_factor;
}

template<typename ClockImpl>
typename
sge::timer::clocks::adjustable<ClockImpl>::time_point
sge::timer::clocks::adjustable<ClockImpl>::now() const
{
	return transformed_time_;
}

#endif
