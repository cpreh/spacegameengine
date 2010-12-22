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
#include "../mouse_grab.hpp"
#include "../device/event.hpp"
#include "../device/event_demuxer.hpp"
#include "../device/parameters.hpp"
#include <X11/Xlib.h>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <X11/extensions/XInput2.h>

namespace
{

sge::input::mouse::button_code::type
mouse_key_code(
	unsigned x11code
);

}

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
	grab_(),
	button_signal_(),
	axis_signal_()
{}

sge::x11input::mouse::~mouse()
{
}

void
sge::x11input::mouse::grab()
{
#if 0
	grab_.take(
		fcppt::make_unique_ptr<
			x11input::mouse_grab
		>(
			window_,
			cursor_
		)
	);
#endif
}

void
sge::x11input::mouse::ungrab()
{
	grab_.reset();
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

#include <sge/exception.hpp>
#include <iostream>

void
sge::x11input::mouse::on_motion(
	x11input::device::event const &_event
)
	XIValuatorState const &valuators(
		_event.get().valuators
	);

	double *valuator = valuators.values;
	std::cout << "-------------- " << valuators.mask_len * 8 << '\n';

    for (int i = 0; i < valuators.mask_len * 8; i++)
        if (XIMaskIsSet(valuators.mask, i)) {
            std::cout << '\t' << i << ": " << *valuator << '\n';
            valuator++;
        }
}

void
sge::x11input::mouse::on_button_down(
	x11input::device::event const &_event
)
{
	button_event(
		_event,
		true
	);
}

void
sge::x11input::mouse::on_button_up(
	x11input::device::event const &_event
)
{
	button_event(
		_event,
		false
	);
}

void
sge::x11input::mouse::button_event(
	x11input::device::event const &_event,
	bool const _pressed
)
{
#if 0
	button_signal_(
		input::mouse::button_event(
			::mouse_key_code(
				_event.get().xbutton.button
			),
			_pressed
		)
	);
#endif
}

void
sge::x11input::mouse::private_mouse_motion(
	mouse_coordinate const _deltax,
	mouse_coordinate const _deltay
)
{
#if 0
	if(
		_deltax
	)
		axis_signal_(
			input::mouse::axis_event(
				input::mouse::axis::x,
				_deltax
			)
		);

	if(
		_deltay
	)
		axis_signal_(
			input::mouse::axis_event(
				input::mouse::axis::y,
				_deltay
			)
		);
#endif
}

namespace
{

sge::input::mouse::button_code::type
mouse_key_code(
	unsigned const _x11code
)
{
	switch(
		_x11code
	)
	{
	case 1:
		return sge::input::mouse::button_code::left;
	case 2:
		return sge::input::mouse::button_code::middle;
	case 3:
		return sge::input::mouse::button_code::right;
	}
	
	return sge::input::mouse::button_code::unknown;
}

}
