/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/timer/scoped_frame_limiter.hpp>
#include <fcppt/time/sleep_any.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <fcppt/config/external_end.hpp>


sge::timer::scoped_frame_limiter::scoped_frame_limiter(
	ticks_per_second const _desired_fps
)
:
	before_frame_(
		clock_type::now()
	),
	minimum_frame_length_(
		boost::chrono::duration_cast<
			clock_type::duration
		>(
			boost::chrono::seconds(1)
		)
		/
		static_cast<
			clock_type::rep
		>(
			_desired_fps
		)
	)
{
}

sge::timer::scoped_frame_limiter::~scoped_frame_limiter()
{
	clock_type::duration const diff(
		clock_type::now() - before_frame_
	);

	if(
		diff > minimum_frame_length_
	)
		return;

	fcppt::time::sleep_any(
		minimum_frame_length_ - diff
	);
}
