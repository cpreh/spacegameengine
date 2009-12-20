/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TIME_TIMER_HPP_INCLUDED
#define SGE_TIME_TIMER_HPP_INCLUDED

#include <sge/time/unit.hpp>
#include <sge/time/funit.hpp>
#include <sge/time/fun.hpp>
#include <sge/time/activation_state.hpp>
#include <sge/time/expiration_state.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace time
{

class resolution;

class timer {
	FCPPT_NONCOPYABLE(timer)
public:
	typedef funit      frames_type;
	typedef unit       interval_type;

	SGE_SYMBOL explicit timer(
		resolution const &interval,
		activation_state::type active_
			= activation_state::active,
		fun const & = default_time_fun(),
		expiration_state::type expire_
			= expiration_state::not_expired);
	SGE_SYMBOL frames_type update();
	SGE_SYMBOL bool update_b();
	SGE_SYMBOL frames_type elapsed_frames() const;
	SGE_SYMBOL frames_type reset();
	SGE_SYMBOL bool expired() const;
	SGE_SYMBOL interval_type interval() const;
	SGE_SYMBOL interval_type last_time() const;
	SGE_SYMBOL void interval(
		resolution const&);
	SGE_SYMBOL void activate();
	SGE_SYMBOL void deactivate();
	SGE_SYMBOL bool active() const;
	SGE_SYMBOL void expire();
private:
	fun const fun_;
	interval_type
		interval_,
		last_time_;
	activation_state::type active_;
	expiration_state::type expired_;
};

}
}

#endif
