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


#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/joypad/event_map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <awl/backends/x11/system/event/processor_fwd.hpp>
#include <fcppt/move.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::object::object(
	awl::backends::x11::system::event::processor &_system_processor,
	sge::evdev::device::fd_unique_ptr _fd,
	sge::evdev::joypad::info const &_info
)
:
	sge::input::joypad::device(),
	sge::evdev::device::object(
		_system_processor,
		fcppt::move(
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
		this->absolute_axis_event(
			_event
		);

		break;
	case EV_KEY:
		this->button_event(
			_event
		);

		break;
	case EV_REL:
		this->relative_axis_event(
			_event
		);

		break;
	}
}

void
sge::evdev::joypad::object::absolute_axis_event(
	sge::evdev::device::event const &_event
)
{
	sge::evdev::joypad::event_map::absolute_axis_map const &map(
		info_.event_map().absolute_axis()
	);

	sge::evdev::joypad::event_map::absolute_axis_map::const_iterator const it(
		map.find(
			sge::evdev::device::event_type(
				_event.get().code
			)
		)
	);

	if(
		it == map.end()
	)
		return;

	absolute_axis_(
		sge::input::joypad::absolute_axis_event(
			sge::input::joypad::absolute_axis(
				info_.input_info().absolute_axis()[
					it->second
				].code(),
				it->second
			),
			_event.get().value
		)
	);
}

void
sge::evdev::joypad::object::button_event(
	sge::evdev::device::event const &_event
)
{
	sge::evdev::joypad::event_map::button_map const &map(
		info_.event_map().buttons()
	);

	sge::evdev::joypad::event_map::button_map::const_iterator const it(
		map.find(
			sge::evdev::device::event_type(
				_event.get().code
			)
		)
	);

	if(
		it == map.end()
	)
		return;

	button_(
		sge::input::joypad::button_event(
			it->second,
			_event.get().value != 0u
		)
	);

}

void
sge::evdev::joypad::object::relative_axis_event(
	sge::evdev::device::event const &_event
)
{
	sge::evdev::joypad::event_map::relative_axis_map const &map(
		info_.event_map().relative_axis()
	);

	sge::evdev::joypad::event_map::relative_axis_map::const_iterator const it(
		map.find(
			sge::evdev::device::event_type(
				_event.get().code
			)
		)
	);

	if(
		it == map.end()
	)
		return;

	relative_axis_(
		sge::input::joypad::relative_axis_event(
			sge::input::joypad::relative_axis(
				info_.input_info().relative_axis()[
					it->second
				].code(),
				it->second
			),
			_event.get().value
		)
	);

}
