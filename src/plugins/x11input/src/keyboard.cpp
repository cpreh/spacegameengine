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


#include "../keyboard.hpp"
#include "../keyboard_key.hpp"
#include "../device/window_demuxer.hpp"
#include "../device/window_event.hpp"
#include "../device/parameters.hpp"
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/to_modifier.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <X11/extensions/XInput2.h>

sge::x11input::keyboard::keyboard(
	x11input::device::parameters const &_param
)
:
	window_(
		_param.window()
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_param.window_demuxer().register_callback(
					awl::backends::x11::system::event::type(
						XI_KeyPress
					),
					_param.id(),
					std::tr1::bind(
						&keyboard::on_key_press,
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
						XI_KeyRelease
					),
					_param.id(),
					std::tr1::bind(
						&keyboard::on_key_release,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	key_signal_(),
	key_repeat_signal_(),
	modifiers_(
		sge::input::keyboard::mod_state::null()
	)
{
}

sge::x11input::keyboard::~keyboard()
{
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
sge::x11input::keyboard::on_key_press(
	x11input::device::window_event const &_event
)
{
	on_key_event(
		_event,
		true
	);
}

void
sge::x11input::keyboard::on_key_release(
	x11input::device::window_event const &_event
)
{
	on_key_event(
		_event,
		false
	);
}

void
sge::x11input::keyboard::on_key_event(
	x11input::device::window_event const &_event,
	bool const _pressed
)
{
	input::keyboard::key const key(
		x11input::keyboard_key(
			window_->display(),
			_event.get().detail
		)
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
			] = _pressed;
	}

	if(
		_event.get().flags & XIKeyRepeat
	)
		key_repeat_signal_(
			input::keyboard::key_repeat_event(
				key
			)
		);
	else
		key_signal_(
			input::keyboard::key_event(
				key,
				_pressed
			)
		);
}
