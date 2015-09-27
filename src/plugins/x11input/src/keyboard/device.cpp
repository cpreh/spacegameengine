/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/key/repeated.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/keyboard/key_from_event.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::keyboard::device::device(
	sge::x11input::device::parameters const &_param
)
:
	sge::input::keyboard::device(),
	sge::x11input::device::object(
		_param.id()
	),
	key_signal_(),
	window_(
		_param.window()
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_KeyPress
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::keyboard::device::on_key_press,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_KeyRelease
				),
				_param.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::keyboard::device::on_key_release,
						this,
						std::placeholders::_1
					)
				}
			)
		)
		.move_container()
	)
{
}

sge::x11input::keyboard::device::~device()
{
}

fcppt::signal::auto_connection
sge::x11input::keyboard::device::key_callback(
	sge::input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

void
sge::x11input::keyboard::device::on_key_press(
	sge::x11input::device::window_event const &_event
)
{
	if(
		!sge::x11input::key::repeated(
			_event.get()
		)
	)
		key_signal_(
			sge::input::keyboard::key_event(
				sge::x11input::keyboard::key_from_event(
					window_.display(),
					_event.get()
				),
				sge::input::key::pressed{
					true
				}
			)
		);
}

void
sge::x11input::keyboard::device::on_key_release(
	sge::x11input::device::window_event const &_event
)
{
	key_signal_(
		sge::input::keyboard::key_event(
			sge::x11input::keyboard::key_from_event(
				window_.display(),
				_event.get()
			),
			sge::input::key::pressed{
				false
			}
		)
	);
}
