/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TIMER_BASIC_IMPL_HPP_INCLUDED
#define SGE_TIMER_BASIC_IMPL_HPP_INCLUDED

#include <sge/timer/basic_decl.hpp>
#include <sge/timer/parameters_impl.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/time_point_arithmetic.hpp>
#include <fcppt/chrono/time_point_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
template<typename Clock>
sge::timer::basic<Clock>::basic(
	parameters const &params)
:
	base(
		params.clock()),
	interval_(
		params.interval()),
	active_(
		params.active()),
	expired_(
		params.expired()),
	last_time_(
		this->now())
{
}
FCPPT_PP_POP_WARNING

template<typename Clock>
bool
sge::timer::basic<Clock>::expired() const
{
	return
		active_ && (expired_ || (this->now() - last_time_).count() > interval_.count());
}

template<typename Clock>
void
sge::timer::basic<Clock>::expired(
	bool const _expired)
{
	expired_ =
		_expired;
}

template<typename Clock>
bool
sge::timer::basic<Clock>::active() const
{
	return active_;
}

template<typename Clock>
void
sge::timer::basic<Clock>::active(
	bool const _active)
{
	if(active_ == _active)
		return;

	if(active_)
	{
		active_ = false;
	}
	else
	{
		this->reset();
		active_ = true;
	}
}

template<typename Clock>
template<typename NewDuration>
NewDuration const
sge::timer::basic<Clock>::interval() const
{
	return
		fcppt::chrono::duration_cast<NewDuration>(
			interval_);
}

template<typename Clock>
template<typename NewDuration>
void
sge::timer::basic<Clock>::interval(
	NewDuration const &_interval)
{
	interval_ =
		fcppt::chrono::duration_cast<duration>(
			_interval);
	this->reset();
}

template<typename Clock>
typename
sge::timer::basic<Clock>::time_point const
sge::timer::basic<Clock>::now() const
{
	return this->clock_base().now();
}

template<typename Clock>
typename
sge::timer::basic<Clock>::time_point const
sge::timer::basic<Clock>::last_time() const
{
	return last_time_;
}

template<typename Clock>
void
sge::timer::basic<Clock>::reset()
{
	last_time_ = this->now();
	expired_ = false;
}

#endif
