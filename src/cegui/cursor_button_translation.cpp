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


#include "cursor_button_translation.hpp"
#include "cursor_button_map.hpp"
#include <sge/input/cursor/button_code.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <CEGUIInputEvent.h>
#include <fcppt/config/external_end.hpp>

namespace
{

sge::cegui::cursor_button_map const buttons(
	fcppt::assign::make_container<
		sge::cegui::cursor_button_map::map_type
	>(
		std::make_pair(
			sge::input::cursor::button_code::left,
			CEGUI::LeftButton
		)
	)(
		std::make_pair(
			sge::input::cursor::button_code::right,
			CEGUI::RightButton
		)
	)(
		std::make_pair(
			sge::input::cursor::button_code::middle,
			CEGUI::MiddleButton
		)
	)
);

}

sge::cegui::cursor_button_map const &
sge::cegui::cursor_button_translation()
{
	return buttons;
}
