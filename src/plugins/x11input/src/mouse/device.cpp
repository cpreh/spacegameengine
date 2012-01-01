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


#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/x11input/mask_is_set.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/raw_demuxer.hpp>
#include <sge/x11input/device/raw_event.hpp>
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
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::mouse::device::device(
	x11input::device::parameters const &_param
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
			fcppt::signal::shared_connection(
				_param.raw_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_RawMotion
					),
					_param.id(),
					std::tr1::bind(
						&device::on_motion,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_ButtonPress
					),
					_param.id(),
					std::tr1::bind(
						&device::on_button_down,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_ButtonRelease
					),
					_param.id(),
					std::tr1::bind(
						&device::on_button_up,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	info_(
		x11input::mouse::info(
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
	input::mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::mouse::device::button_callback(
	input::mouse::button_callback const &_callback
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
	x11input::device::raw_event const &_event
)
{
	XIValuatorState const &valuators(
		_event.get().valuators
	);

	if(
		valuators.mask_len == 0
	)
		return;

	double const *valuator(
		valuators.values
	);

	for(
		int index = 0;
		index < valuators.mask_len * 8;
		++index, ++valuator
	)
	{
		if(
			x11input::mask_is_set(
				valuators.mask,
				index
			)
		)
			axis_signal_(
				input::mouse::axis_event(
					x11input::mouse::axis(
						index,
						info_.axis()
					),
					x11input::mouse::axis_value(
						*valuator
					)
				)
			);
	}
}

void
sge::x11input::mouse::device::on_button_down(
	x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		true
	);
}

void
sge::x11input::mouse::device::on_button_up(
	x11input::device::window_event const &_event
)
{
	this->button_event(
		_event,
		false
	);
}

void
sge::x11input::mouse::device::button_event(
	x11input::device::window_event const &_event,
	bool const _pressed
)
{
	button_signal_(
		input::mouse::button_event(
			input::mouse::button(
				x11input::mouse::button(
					_event,
					info_.buttons()
				)
			),
			_pressed
		)
	);
}
