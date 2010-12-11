/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../device_info.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <X11/extensions/XInput2.h>

sge::x11input::device_info::device_info(
	awl::backends::x11::display_ptr const _display,
	int const _type
)
:
	devices_(
		::XIQueryDevice(
			_display->get(),
			XIAllDevices,
			&size_
		)
	)
{
	if(
		devices_ == 0
	)
		throw sge::input::exception(
			FCPPT_TEXT("XIQueryDevice failed!")
		);
}

sge::x11input::device_info::~device_info()
{
	::XIFreeDeviceInfo(
		devices_
	);
}

XIDeviceInfo const &
sge::x11input::device_info::operator[](
	size_type const _index
) const
{
	return devices_[_index];
}

sge::x11input::device_info::size_type
sge::x11input::device_info::size() const
{
	return size_;
}
