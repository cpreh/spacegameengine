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


#include "../keyboard_repeat.hpp"
#include <sge/windows/windows.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/resolution.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sge::time::resolution const
sge::dinput::keyboard_repeat()
{
	int ret = 0;
	if(
		SystemParametersInfo(
			SPI_GETKEYBOARDDELAY,
			0,
			&ret,
			0
		) == 0
	)
		throw exception(
			FCPPT_TEXT("SystemParametersInfo() failed!")
		);

	return time::millisecond(
		ret * 250
	);
}
