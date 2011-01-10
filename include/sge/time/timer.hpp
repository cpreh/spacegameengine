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


#ifndef SGE_TIME_TIMER_HPP_INCLUDED
#define SGE_TIME_TIMER_HPP_INCLUDED

#include <sge/time/duration.hpp>
#include <sge/time/unit.hpp>
#include <sge/time/funit.hpp>
#include <sge/time/callback.hpp>
#include <sge/time/default_callback.hpp>
#include <sge/time/activation_state.hpp>
#include <sge/time/expiration_state.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace time
{

class timer
{
	FCPPT_NONCOPYABLE(timer)
public:
	typedef funit      frames_type;
	typedef unit       interval_type;

	SGE_TIME_SYMBOL explicit timer(
		duration const &interval,
		activation_state::type active_
			= activation_state::active,
		callback const & = default_callback(),
		expiration_state::type expire_
			= expiration_state::not_expired
	);

	SGE_TIME_SYMBOL frames_type
	update();

	SGE_TIME_SYMBOL bool
	update_b();

	SGE_TIME_SYMBOL frames_type
	elapsed_frames() const;

	SGE_TIME_SYMBOL frames_type
	reset();

	SGE_TIME_SYMBOL bool
	expired() const;

	SGE_TIME_SYMBOL interval_type
	interval() const;

	SGE_TIME_SYMBOL interval_type
	last_time() const;

	SGE_TIME_SYMBOL void
	interval(
		duration const &
	);

	SGE_TIME_SYMBOL void
	activate();

	SGE_TIME_SYMBOL void
	deactivate();

	SGE_TIME_SYMBOL bool
	active() const;

	SGE_TIME_SYMBOL void
	expire();
private:
	callback const callback_;

	interval_type
		interval_,
		last_time_;

	activation_state::type active_;

	expiration_state::type expired_;
};

}
}

#endif
