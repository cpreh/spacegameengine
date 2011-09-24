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


#include "../info_base.hpp"
#include "../id.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::device::info_base::info_base(
	awl::backends::x11::display &_display,
	x11input::device::id const _id
)
:
	size_(
		0
	),
	devices_(
		::XIQueryDevice(
			_display.get(),
			_id.get(),
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

sge::x11input::device::info_base::~info_base()
{
	::XIFreeDeviceInfo(
		devices_
	);
}

XIDeviceInfo const *
sge::x11input::device::info_base::get() const
{
	return devices_;
}

sge::x11input::device::info_base::size_type
sge::x11input::device::info_base::size() const
{
	return size_;
}
