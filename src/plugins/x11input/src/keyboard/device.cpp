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


#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/to_modifier.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/keyboard/fake_core_event.hpp>
#include <sge/x11input/keyboard/key_code_to_key_sym.hpp>
#include <sge/x11input/keyboard/looked_up_string.hpp>
#include <sge/x11input/keyboard/lookup_string.hpp>
#include <sge/x11input/keyboard/translate_key_code.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::keyboard::device::device(
	x11input::device::parameters const &_param,
	x11input::input_context const &_input_context
)
:
	sge::input::keyboard::device(),
	sge::x11input::device::object(
		_param.id()
	),
	window_(
		_param.window()
	),
	input_context_(_input_context),
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
						&device::on_key_press,
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
						&device::on_key_release,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	key_signal_(),
	key_repeat_signal_(),
	char_signal_(),
	modifiers_(
		sge::input::keyboard::mod_state::null()
	)
{
}

sge::x11input::keyboard::device::~device()
{
}

fcppt::signal::auto_connection
sge::x11input::keyboard::device::key_callback(
	input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::keyboard::device::key_repeat_callback(
	input::keyboard::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::keyboard::device::char_callback(
	input::keyboard::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::x11input::keyboard::device::mod_state() const
{
	return modifiers_;
}

void
sge::x11input::keyboard::device::on_key_press(
	x11input::device::window_event const &_event
)
{
	keyboard::fake_core_event(
		window_,
		_event
	);

	sge::x11input::keyboard::looked_up_string const lookup(
		x11input::keyboard::lookup_string(
			input_context_,
			_event.get()
		)
	);

	bool const is_repeated(
		_event.get().flags & XIKeyRepeat
	);

	if(
		is_repeated
	)
		key_repeat_signal_(
			input::keyboard::key_repeat_event(
				lookup.key_code()
			)
		);
	else
	{
		this->update_modifiers(
			lookup.key_code(),
			true
		);

		key_signal_(
			input::keyboard::key_event(
				lookup.key_code(),
				true
			)
		);
	}

	x11input::keyboard::char_vector const &char_codes(
		lookup.char_codes()
	);

	for(
		x11input::keyboard::char_vector::const_iterator element_it(
			char_codes.begin()
		);
		element_it != char_codes.end();
		++element_it
	)
		char_signal_(
			input::keyboard::char_event(
				*element_it,
				is_repeated
			)
		);
}

void
sge::x11input::keyboard::device::on_key_release(
	x11input::device::window_event const &_event
)
{
	keyboard::fake_core_event(
		window_,
		_event
	);

	sge::input::keyboard::key_code::type const key_code(
		x11input::keyboard::translate_key_code(
			x11input::keyboard::key_code_to_key_sym(
				window_.display(),
				_event.get().detail
			)
		)
	);

	this->update_modifiers(
		key_code,
		false
	);

	key_signal_(
		input::keyboard::key_event(
			key_code,
			false
		)
	);
}

void
sge::x11input::keyboard::device::update_modifiers(
	sge::input::keyboard::key_code::type const _key_code,
	bool const _pressed
)
{
	sge::input::keyboard::optional_modifier const mod(
		sge::input::keyboard::to_modifier(
			_key_code
		)
	);

	if(
		mod
	)
		modifiers_[
			*mod
		] = _pressed;
}
