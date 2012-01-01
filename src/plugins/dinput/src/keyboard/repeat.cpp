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


#include <sge/dinput/keyboard/repeat.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/chrono/duration_impl.hpp>


sge::dinput::keyboard::repeat_duration const
sge::dinput::keyboard::repeat()
{
	int ret = 0;

	if(
		::SystemParametersInfo(
			SPI_GETKEYBOARDDELAY,
			0,
			&ret,
			0
		) == 0
	)
		throw sge::input::exception(
			FCPPT_TEXT("SystemParametersInfo() failed!")
		);

	return
		keyboard::repeat_duration(
			ret * 250
		);
}
