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


#ifndef SGE_TIMER_BASIC_DECL_HPP_INCLUDED
#define SGE_TIMER_BASIC_DECL_HPP_INCLUDED

#include <sge/timer/basic_fwd.hpp>
#include <sge/timer/time_point.hpp>
#include <sge/timer/callback.hpp>
#include <sge/timer/parameters_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace timer
{
template<typename Duration,typename Clock>
class basic
{
FCPPT_NONCOPYABLE(
	basic);
public:
	typedef
	timer::parameters<Duration,Clock>
	parameters;

	typedef
	Clock
	clock;

	typedef
	Duration
	duration;

	explicit
	basic(
		parameters const &);

	bool
	expired() const;

	void
	expired(
		bool);

	bool
	active() const;

	void
	active(
		bool);

	typename timer::callback<Clock>::type const
	callback() const;

	Duration const
	interval() const;

	void
	interval(
		Duration const &);

	typename timer::time_point<Clock>::type
	last_time() const;

	void
	reset();
private:
	typename Clock::duration interval_;
	typename timer::callback<Clock>::type callback_;
	bool active_;
	bool expired_;
	typename timer::time_point<Clock>::type last_time_;
};
}
}

#endif
