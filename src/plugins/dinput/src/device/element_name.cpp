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


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/element_name.hpp>
#include <sge/input/info/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


sge::input::info::optional_string const
sge::dinput::device::element_name(
	DIDEVICEOBJECTINSTANCE const &_data
)
{
	return
		_data.dwSize
		<=
		offsetof(
			DIDEVICEOBJECTINSTANCE,
			tszName
		)
		?
			sge::input::info::optional_string()
		:
			sge::input::info::optional_string(
				fcppt::string(
					_data.tszName
				)
			);
}
