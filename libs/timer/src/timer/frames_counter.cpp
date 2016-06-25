/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/timer/basic_impl.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sge::timer::frames_counter::frames_counter()
:
	timer_(
		sge::timer::parameters<
			clock
		>(
			std::chrono::seconds(
				1
			)
		)
	),
	current_frames_(
		0
	),
	display_frames_(
		0
	)
{
}

void
sge::timer::frames_counter::update()
{
	++current_frames_;

	if(
		sge::timer::reset_when_expired(
			timer_
		)
	)
	{
		display_frames_ = current_frames_;

		current_frames_ = 0;
	}
}

sge::timer::frames_counter::counter
sge::timer::frames_counter::frames() const
{
	return
		display_frames_;
}

fcppt::string
sge::timer::frames_counter::frames_str() const
{
	return
		fcppt::insert_to_fcppt_string(
			this->frames()
		);
}

sge::timer::frames_counter::~frames_counter()
{
}
