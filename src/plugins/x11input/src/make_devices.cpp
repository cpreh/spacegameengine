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


#include "../make_devices.hpp"
#include "../device_info.hpp"
#include "../device_parameters.hpp"
#include "../keyboard.hpp"
#include "../mouse.hpp"
#include "../cursor.hpp"
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/shared_ptr.hpp>
#include <vector>

template<
	typename Ret
>
std::vector<
	fcppt::shared_ptr<
		Ret
	>
> const
sge::x11input::make_devices(
	int const _type,
	awl::backends::x11::window::instance_ptr const _window,
	awl::backends::x11::system::event::processor_ptr const _processor
)
{
	std::vector<
		fcppt::shared_ptr<
			Ret
		>
	> ret_devices;

	x11input::device_info const devices(
		_window->display(),
		_type
	);

	for(
		int index = 0;
		index < devices.size();
		++index
	)
	{
		XIDeviceInfo const &device(
			devices[index]
		);

		assert(
			device.use == _type
		);

		ret_devices.push_back(
			fcppt::make_shared_ptr<
				Ret
			>(
				x11input::device_parameters(
					device.deviceid,
					_window,
					_processor
				)
			)
		);
	}
}

#define SGE_X11INPUT_INSTANTIATE_MAKE_DEVICES(\
	device\
)\
template \
std::vector<\
	fcppt::shared_ptr<\
		device\
	> \
> const \
sge::x11input::make_devices<\
	device\
>(\
	int,\
	awl::backends::x11::window::instance_ptr,\
	awl::backends::x11::system::event::processor_ptr\
);

SGE_X11INPUT_INSTANTIATE_MAKE_DEVICES(
	sge::x11input::keyboard
)

SGE_X11INPUT_INSTANTIATE_MAKE_DEVICES(
	sge::x11input::mouse
)

SGE_X11INPUT_INSTANTIATE_MAKE_DEVICES(
	sge::x11input::cursor
)
