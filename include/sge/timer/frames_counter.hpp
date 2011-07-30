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


#ifndef SGE_TIMER_FRAMES_COUNTER_HPP_INCLUDED
#define SGE_TIMER_FRAMES_COUNTER_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace timer
{
class frames_counter
{
FCPPT_NONCOPYABLE(
	frames_counter);
public:
	typedef
	clocks::standard
	clock;

	typedef
	unsigned long
	frame_counter;

	frames_counter()
	:
		timer_(
			timer::parameters<clock>(
				fcppt::chrono::seconds(
					1))),
		current_frames_(
			0),
		display_frames_(
			0)
	{
	}

	void
	update()
	{
		++current_frames_;

		if(
			timer::reset_when_expired(
				timer_))
		{
			display_frames_ = current_frames_;
			current_frames_ = 0;
		}
	}

	frame_counter
	frames() const
	{
		return display_frames_;
	}

	fcppt::string const
	frames_str() const
	{
		return 
			fcppt::lexical_cast<fcppt::string>(
				this->frames());
	}

	~frames_counter()
	{
	}
private:
	timer::basic<clock> timer_;
	frame_counter current_frames_;
	frame_counter display_frames_;
};
}
}

#endif
