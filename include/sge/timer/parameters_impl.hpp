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


#ifndef SGE_TIMER_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/timer/parameters_decl.hpp>
#include <sge/timer/callback.hpp>

template<typename Duration,typename Clock>
sge::timer::parameters<Duration,Clock>::parameters(
	Duration const &_interval)
:
	interval_(
		_interval),
	active_(
		true),
	expired_(
		false),
	callback_(
		&Clock::now)
{
}

template<typename Duration,typename Clock>
sge::timer::parameters<Duration,Clock> &
sge::timer::parameters<Duration,Clock>::active(
	bool const _active)
{
	active_ = 
		_active;
	return 
		*this;
}

template<typename Duration,typename Clock>
sge::timer::parameters<Duration,Clock> &
sge::timer::parameters<Duration,Clock>::expired(
	bool const _expired)
{
	expired_ = 
		_expired;
	return 
		*this;
}

template<typename Duration,typename Clock>
sge::timer::parameters<Duration,Clock> &
sge::timer::parameters<Duration,Clock>::callback(
	typename timer::callback<Clock>::type const &_callback)
{
	callback_ = 
		_callback;
	return 
		*this;
}

template<typename Duration,typename Clock>
Duration const
sge::timer::parameters<Duration,Clock>::interval() const
{
	return interval_;
}

template<typename Duration,typename Clock>
bool
sge::timer::parameters<Duration,Clock>::active() const
{
	return 
		active_;
}

template<typename Duration,typename Clock>
bool
sge::timer::parameters<Duration,Clock>::expired() const
{
	return
		expired_;
}

template<typename Duration,typename Clock>
typename sge::timer::callback<Clock>::type const
sge::timer::parameters<Duration,Clock>::callback() const
{
	return callback_;
}

#endif
