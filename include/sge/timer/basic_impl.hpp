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


#ifndef SGE_TIMER_BASIC_IMPL_HPP_INCLUDED
#define SGE_TIMER_BASIC_IMPL_HPP_INCLUDED

#include <sge/timer/basic_decl.hpp>
#include <sge/timer/parameters_impl.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/time_point_impl.hpp>
#include <fcppt/chrono/time_point_arithmetic.hpp>

template<typename Duration,typename Clock>
sge::timer::basic<Duration,Clock>::basic(
	parameters const &params)
:
	interval_(
		fcppt::chrono::duration_cast<typename Clock::duration>(
			params.interval())),
	callback_(
		params.callback()),
	active_(
		params.active()),
	expired_(
		params.expired()),
	last_time_(
		params.callback()())
{
}

template<typename Duration,typename Clock>
bool
sge::timer::basic<Duration,Clock>::expired() const
{
	return 
		this->active() && (expired_ || (this->callback_() - this->last_time()).count() > interval_.count());
}

template<typename Duration,typename Clock>
void
sge::timer::basic<Duration,Clock>::expired(
	bool const _expired)
{
	expired_ = 
		_expired;
}

template<typename Duration,typename Clock>
bool
sge::timer::basic<Duration,Clock>::active() const
{
	return active_;
}

template<typename Duration,typename Clock>
void
sge::timer::basic<Duration,Clock>::active(
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

template<typename Duration,typename Clock>
typename sge::timer::callback<Clock>::type const
sge::timer::basic<Duration,Clock>::callback() const
{
	return callback_;
}

template<typename Duration,typename Clock>
Duration const
sge::timer::basic<Duration,Clock>::interval() const
{
	return 
		fcppt::chrono::duration_cast<Duration>(
			interval_);
}

template<typename Duration,typename Clock>
void
sge::timer::basic<Duration,Clock>::interval(
	Duration const &_interval)
{
	interval_ = 
		fcppt::chrono::duration_cast<Duration>(
			_interval);
	this->reset();
}

template<typename Duration,typename Clock>
typename sge::timer::time_point<Clock>::type
sge::timer::basic<Duration,Clock>::last_time() const
{
	return last_time_;
}

template<typename Duration,typename Clock>
void
sge::timer::basic<Duration,Clock>::reset()
{
	last_time_ = this->callback_();
	expired_ = false;
}

#endif
