/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "unit.hpp"
#include "funit.hpp"
#include "fun.hpp"
#include <sge/export.hpp>

namespace sge
{
namespace time
{

class resolution;

class timer {
public:
	typedef funit      frames_type;
	typedef unit       interval_type;

	SGE_SYMBOL explicit timer(
		fun const & = default_time_fun());
	SGE_SYMBOL explicit timer(
		resolution const &interval,
		bool active = true,
		fun const & = default_time_fun());
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
private:
	fun           fun_;
	interval_type interval_,
	              last_time_;
	bool          active_;
};

}
}

#endif
