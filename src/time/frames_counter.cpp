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


#include <sge/time/frames_counter.hpp>
#include <sge/time/second.hpp>
#include <fcppt/lexical_cast.hpp>

sge::time::frames_counter::frames_counter()
:
	t(sge::time::second(1)),
	current_frames(0),
	display_frames(0)
{}

void
sge::time::frames_counter::update()
{
	++current_frames;
	if(t.update() > 0)
	{
		display_frames = current_frames;
		current_frames = 0;
	}
}

fcppt::string const
sge::time::frames_counter::frames_str() const
{
	return
		fcppt::lexical_cast<
			fcppt::string
		>(
			frames()
		);
}

sge::time::unit
sge::time::frames_counter::frames() const
{
	return display_frames;
}
