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


#include "../mouse.hpp"
#include "../mouse_axis.hpp"
#include "../mouse_button_code.hpp"
#include "../device/raw_demuxer.hpp"
#include "../device/raw_event.hpp"
#include "../device/window_demuxer.hpp"
#include "../device/window_event.hpp"
#include "../device/parameters.hpp"
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <X11/extensions/XInput2.h>

sge::x11input::mouse::mouse(
	x11input::device::parameters const &_param
)
:
	x11input::device::object(
		_param.id()
	),
	window_(
		_param.window()
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
						&mouse::on_motion,
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
						&mouse::on_button_down,
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
						&mouse::on_button_up,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	button_signal_(),
	axis_signal_()
{
	int const nmodifiers = 1;
	XIGrabModifiers modifiers[nmodifiers];
	modifiers[0].modifiers = 0;

	unsigned char mask[1] = { 0 };

	XIEventMask event_mask =
	{
		_param.id().get(),
		1,
		mask
	};

//	if(
		::XIGrabEnter(
			window_->display()->get(),
			_param.id().get(),
			window_->get(),
			None,
			GrabModeSync,
			GrabModeSync,
			False,
			&event_mask,
			nmodifiers,
			modifiers
		);
//		!= 0
//	)
//		throw sge::input::exception(
//			FCPPT_TEXT("XIGrabEnter() failed!")
//		);
}

sge::x11input::mouse::~mouse()
{
}

void
sge::x11input::mouse::grab()
{
}

void
sge::x11input::mouse::ungrab()
{
}

fcppt::signal::auto_connection
sge::x11input::mouse::button_callback(
	input::mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::mouse::axis_callback(
	input::mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

void
sge::x11input::mouse::on_motion(
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
		index++
	)
	{
		if(
			XIMaskIsSet(
				valuators.mask,
				index
			)
		)
		{
			axis_signal_(
				input::mouse::axis_event(
					x11input::mouse_axis(
						index
					),
					// TODO: how to scale this?
					*valuator
				)
			);
		}

            ++valuator;
	}
}

void
sge::x11input::mouse::on_button_down(
	x11input::device::window_event const &_event
)
{
	button_event(
		_event,
		true
	);
}

void
sge::x11input::mouse::on_button_up(
	x11input::device::window_event const &_event
)
{
	button_event(
		_event,
		false
	);
}

void
sge::x11input::mouse::button_event(
	x11input::device::window_event const &_event,
	bool const _pressed
)
{
	button_signal_(
		input::mouse::button_event(
			x11input::mouse_button_code(
				_event.get().detail
			),
			_pressed
		)
	);
}
