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


#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/x11input/device/foreach_valuator.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/raw_demuxer.hpp>
#include <sge/x11input/device/raw_event.hpp>
#include <sge/x11input/device/valuator_index.hpp>
#include <sge/x11input/device/valuator_value.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/mouse/axis.hpp>
#include <sge/x11input/mouse/axis_value.hpp>
#include <sge/x11input/mouse/button.hpp>
#include <sge/x11input/mouse/device.hpp>
#include <sge/x11input/mouse/info.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::mouse::device::device(
	sge::x11input::device::parameters const &_param
)
:
	sge::input::mouse::device(),
	sge::x11input::device::object(
		_param.id()
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			_param.raw_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_RawMotion
				),
				_param.id(),
				std::bind(
					&sge::x11input::mouse::device::on_motion,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_ButtonPress
				),
				_param.id(),
				std::bind(
					&sge::x11input::mouse::device::on_button_down,
					this,
					std::placeholders::_1
				)
			)
		)
		(
			_param.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_ButtonRelease
				),
				_param.id(),
				std::bind(
					&sge::x11input::mouse::device::on_button_up,
					this,
					std::placeholders::_1
				)
			)
		)
		.move_container()
	),
	info_(
		sge::x11input::mouse::info(
			_param.window().display(),
			_param.info()
		)
	),
	axis_signal_(),
	button_signal_()
{
}

sge::x11input::mouse::device::~device()
{
}

fcppt::signal::auto_connection
sge::x11input::mouse::device::axis_callback(
	sge::input::mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::mouse::device::button_callback(
	sge::input::mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

sge::input::mouse::info const &
sge::x11input::mouse::device::info() const
{
	return info_;
}

void
sge::x11input::mouse::device::on_motion(
	sge::x11input::device::raw_event const &_event
)
{
	sge::x11input::device::foreach_valuator(
		_event.get().valuators,
		std::bind(
			&sge::x11input::mouse::device::process_valuator,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	);
}

void
sge::x11input::mouse::device::process_valuator(
	sge::x11input::device::valuator_index const _index,
	sge::x11input::device::valuator_value const _value
)
{
	axis_signal_(
		sge::input::mouse::axis_event(
			sge::x11input::mouse::axis(
				_index,
				info_.axes()
			),
			sge::x11input::mouse::axis_value(
				_value
			)
		)
	);
}

void
sge::x11input::mouse::device::on_button_down(
	sge::x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		true
	);
}

void
sge::x11input::mouse::device::on_button_up(
	sge::x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		false
	);
}

void
sge::x11input::mouse::device::button_event(
	sge::x11input::device::window_event const &_event,
	bool const _pressed
)
{
	if(
		_event.get().flags
		&
		XIPointerEmulated
	)
		return;

	button_signal_(
		sge::input::mouse::button_event(
			sge::input::mouse::button(
				sge::x11input::mouse::button(
					_event,
					info_.buttons()
				)
			),
			_pressed
		)
	);
}
