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


#include <sge/input/info/optional_string.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/x11input/mouse/button_code.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sge::input::mouse::button_code::type
sge::x11input::mouse::button_code(
	sge::input::info::optional_string const &_info
)
{
	if(
		!_info
	)
		return sge::input::mouse::button_code::unknown;

	fcppt::string const name(
		*_info
	);

	if(
		name == FCPPT_TEXT("Button Left")
	)
		return sge::input::mouse::button_code::left;

	if(
		name == FCPPT_TEXT("Button Right")
	)
		return sge::input::mouse::button_code::right;

	if(
		name == FCPPT_TEXT("Button Middle")
	)
		return sge::input::mouse::button_code::middle;

	return sge::input::mouse::button_code::unknown;
}
