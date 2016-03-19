/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/evdev/device/conditional_event.hpp>
#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/absolute_axis/make_event.hpp>
#include <sge/evdev/joypad/button/make_event.hpp>
#include <sge/evdev/joypad/relative_axis/make_event.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <awl/backends/linux/fd/processor_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::object::object(
	awl::backends::linux::fd::processor &_processor,
	sge::evdev::device::fd_unique_ptr _fd,
	sge::evdev::joypad::info const &_info
)
:
	sge::input::joypad::device(),
	sge::evdev::device::object(
		_processor,
		std::move(
			_fd
		)
	),
	info_(
		_info
	),
	absolute_axis_(),
	button_(),
	relative_axis_()
{
}

sge::evdev::joypad::object::~object()
{
}

fcppt::signal::auto_connection
sge::evdev::joypad::object::absolute_axis_callback(
	sge::input::joypad::absolute_axis_callback const &_callback
)
{
	return
		absolute_axis_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::joypad::object::button_callback(
	sge::input::joypad::button_callback const &_callback
)
{
	return
		button_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::evdev::joypad::object::relative_axis_callback(
	sge::input::joypad::relative_axis_callback const &_callback
)
{
	return
		relative_axis_.connect(
			_callback
		);
}

sge::input::joypad::info const &
sge::evdev::joypad::object::info() const
{
	return
		info_.input_info();
}

void
sge::evdev::joypad::object::process_event(
	sge::evdev::device::event const &_event
)
{
	switch(
		_event.get().type
	)
	{
	case EV_ABS:
		sge::evdev::device::conditional_event(
			_event,
			absolute_axis_,
			info_.event_map().absolute_axis(),
			info_.input_info().absolute_axes(),
			&sge::evdev::joypad::absolute_axis::make_event
		);

		break;
	case EV_KEY:
		sge::evdev::device::conditional_event(
			_event,
			button_,
			info_.event_map().buttons(),
			info_.input_info().buttons(),
			&sge::evdev::joypad::button::make_event
		);

		break;
	case EV_REL:
		sge::evdev::device::conditional_event(
			_event,
			relative_axis_,
			info_.event_map().relative_axis(),
			info_.input_info().relative_axes(),
			&sge::evdev::joypad::relative_axis::make_event
		);

		break;
	}
}
