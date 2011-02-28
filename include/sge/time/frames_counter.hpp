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


#ifndef SGE_TIME_FRAMES_COUNTER_HPP_INCLUDED
#define SGE_TIME_FRAMES_COUNTER_HPP_INCLUDED

#include <sge/time/timer.hpp>
#include <sge/time/unit.hpp>
#include <sge/time/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace time
{

class frames_counter
{
	FCPPT_NONCOPYABLE(
		frames_counter
	);
public:
	SGE_TIME_SYMBOL frames_counter();

	SGE_TIME_SYMBOL ~frames_counter();

	SGE_TIME_SYMBOL void
	update();

	SGE_TIME_SYMBOL fcppt::string const
	frames_str() const;

	SGE_TIME_SYMBOL time::unit
	frames() const;
private:
	sge::time::timer timer_;

	time::unit
		current_frames_,
		display_frames_;
};

}
}

#endif
