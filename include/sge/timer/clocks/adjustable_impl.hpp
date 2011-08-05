/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_TIMER_CLOCKS_ADJUSTABLE_IMPL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_ADJUSTABLE_IMPL_HPP_INCLUDED

#include <sge/timer/clocks/adjustable_decl.hpp>
#include <fcppt/chrono/time_point_arithmetic.hpp>
#include <fcppt/chrono/time_point_impl.hpp>
#include <fcppt/chrono/duration_impl.hpp>

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
	return factor_;
}

template<typename ClockImpl>
typename
sge::timer::clocks::adjustable<ClockImpl>::time_point
sge::timer::clocks::adjustable<ClockImpl>::now() const
{
	return transformed_time_;
}

#endif
