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


#include "../keyboard.hpp"
#include "../keyboard_grab.hpp"
#include "../keyboard_key.hpp"
#include "../device_parameters.hpp"
#include "../select_events.hpp"
#include "../event_data.hpp"
#include <X11/Xlib.h>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/to_modifier.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>

#include <X11/extensions/XInput2.h>

#include <iostream>

sge::x11input::keyboard::keyboard(
	x11input::device_parameters const &_param
)
:
	x11input::device(
		_param.id()
	),
	window_(
		_param.window()
	),
	need_grab_(
		// TODO!
		false // _wnd->fullscreen()
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_param.processor()->register_callback(
					_param.opcode(),
					awl::backends::x11::system::event::type(
						XI_KeyPress
					),
					std::tr1::bind(
						&keyboard::on_key_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_param.processor()->register_callback(
					_param.opcode(),
					awl::backends::x11::system::event::type(
						XI_KeyRelease
					),
					std::tr1::bind(
						&keyboard::on_key_event,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	grab_(),
	key_signal_(),
	key_repeat_signal_(),
	modifiers_(
		sge::input::keyboard::mod_state::null()
	)
{
	x11input::select_events(
		_param.window(),
		_param.id(),
		fcppt::assign::make_container<
			x11input::event_id_container
		>(
			XI_KeyPress
		)
		(
			XI_KeyRelease
		)
	);
}

sge::x11input::keyboard::~keyboard()
{
}

void
sge::x11input::keyboard::grab()
{
	if(
		need_grab_
	)
		grab_.take(
			fcppt::make_unique_ptr<
				x11input::keyboard_grab
			>(
				window_
			)
		);
}

void
sge::x11input::keyboard::ungrab()
{
	grab_.reset();
}

fcppt::signal::auto_connection
sge::x11input::keyboard::key_callback(
	input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::keyboard::key_repeat_callback(
	input::keyboard::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::x11input::keyboard::mod_state() const
{
	return modifiers_;
}

void
sge::x11input::keyboard::on_key_event(
	awl::backends::x11::system::event::object const &_event
)
{
	x11input::event_data const cookie(
		window_->display(),
		_event
	);

	XIDeviceEvent const *const event= static_cast<XIDeviceEvent const *>(cookie.data());

	std::cout << "    device: " << event->deviceid << " (" << event->sourceid << ")\n";
	std::cout << "    detail: " << event->detail << '\n';
	if (event->flags & XIKeyRepeat)
		std::cout << "    event is a key repeat.\n";
	
	#if 0
	for(
		int i = 0;
		i < event->buttons.mask_len;
		++i
	)
		for(
			unsigned j = 0;
			j < 8;
			++j
		)
			std::cout << std::boolalpha << (event->buttons.mask[i] & (1 << j)) << ' ';

	std::cout << '\n';

	#endif
	if(event->event != window_->get())
		std::cout << "not for this window\n";
	else
		std::cout << "for this window\n";
#if 0
	std::cout << "KEYBOARD\n";

	XEvent const &xev(
		_event.get()
	);

	XKeyEvent const &key_event(
		xev.xkey
	);

	input::keyboard::key const key(
		x11input::keyboard_key(
			key_event
		)
	);

	// check for repeated key (thanks to SDL)
	if(
		xev.type == KeyRelease
		&&
		::XPending(
			window_->display()->get()
		)
	)
	{
		XEvent peek;

		::XPeekEvent(
			window_->display()->get(),
			&peek
		);
		
		if(
			peek.type == KeyPress &&
			peek.xkey.keycode == xev.xkey.keycode &&
			(peek.xkey.time - xev.xkey.time) < 2
		)
		{
			::XNextEvent(
				window_->display()->get(),
				&peek
			);

			key_repeat_signal_(
				key
			);

			return;
		}
	}

	bool const is_pressed(
		xev.type == KeyPress
	);

	{	
		sge::input::keyboard::optional_modifier const mod(
			sge::input::keyboard::to_modifier(
				key.code()
			)
		);

		if(
			mod
		)
			modifiers_[
				*mod
			] = is_pressed;
	}

	key_signal_(
		input::keyboard::key_event(
			key,
			is_pressed
		)
	);
#endif
}
