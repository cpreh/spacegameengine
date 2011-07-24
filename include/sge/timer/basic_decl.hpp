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
template<typename Clock>
class basic
{
FCPPT_NONCOPYABLE(
	basic);
public:
	typedef
	Clock
	clock;

	typedef
	timer::parameters<clock>
	parameters;

	typedef typename
	clock::duration
	duration;

	typedef typename 
	timer::callback<clock>::type
	callback_type;

	typedef typename 
	timer::time_point<clock>::type
	time_point;

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

	callback_type const
	callback() const;

	template<typename NewDuration>
	NewDuration const
	interval() const;

	template<typename NewDuration>
	void
	interval(
		NewDuration const &);

	time_point const
	last_time() const;

	void
	reset();
private:
	duration interval_;
	callback_type callback_;
	bool active_;
	bool expired_;
	time_point last_time_;
};
}
}

#endif
