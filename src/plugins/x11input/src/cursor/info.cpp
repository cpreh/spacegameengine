/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11input/cursor/info.hpp>
#include <sge/x11input/cursor/scroll_valuator_map.hpp>


sge::x11input::cursor::info::info(
	sge::x11input::cursor::scroll_valuator_map const &_scroll_valuators
)
:
	scroll_valuators_(
		_scroll_valuators
	)
{
}

sge::x11input::cursor::scroll_valuator_map &
sge::x11input::cursor::info::scroll_valuators()
{
	return scroll_valuators_;
}
