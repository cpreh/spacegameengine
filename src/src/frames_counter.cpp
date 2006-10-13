/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sstream>
#include "../frames_counter.hpp"

sge::frames_counter::frames_counter()
: t(1000),
  current_frames(0),
  display_frames(0)
{}

void sge::frames_counter::update()
{
	++current_frames;
	if(t.update())
	{
		display_frames = current_frames;
		current_frames = 0;
	}
}

std::string sge::frames_counter::frames_str() const
{
	std::ostringstream oss;
	oss << frames();
	return oss.str();
}
unsigned sge::frames_counter::frames() const { return display_frames; }
