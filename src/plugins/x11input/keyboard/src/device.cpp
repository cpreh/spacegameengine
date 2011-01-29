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


#include "../device.hpp"
#include "../key_code_to_key_sym.hpp"
#include "../keys.hpp"
#include "../looked_up_string.hpp"
#include "../lookup_string.hpp"
#include "../translate_key_code.hpp"
#include "../../device/window_demuxer.hpp"
#include "../../device/window_event.hpp"
#include "../../device/parameters.hpp"
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/to_modifier.hpp>
#include <awl/backends/x11/system/event/object.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <X11/extensions/XInput2.h>

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
	modifiers_(
		sge::input::keyboard::mod_state::null()
	)
{
}

sge::x11input::keyboard::device::~device()
{
}

void
sge::x11input::keyboard::device::on_enter()
{
}

void
sge::x11input::keyboard::device::on_leave()
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
	sge::x11input::keyboard::looked_up_string const lookup(
		x11input::keyboard::lookup_string(
			input_context_,
			_event.get()
		)
	);

	x11input::keyboard::key_vector const keys(
		x11input::keyboard::keys(
			lookup
		)
	);

	assert(
		!keys.empty()
	);

	if(
		_event.get().flags & XIKeyRepeat
	)
	{
		BOOST_FOREACH(
			x11input::keyboard::key_vector::const_reference key,
			keys
		)
			key_repeat_signal_(
				input::keyboard::key_repeat_event(
					key
				)
			);
	}
	else
	{
		this->update_modifiers(
			lookup.key_code(),
			true
		);

		BOOST_FOREACH(
			x11input::keyboard::key_vector::const_reference key,
			keys
		)
			key_signal_(
				input::keyboard::key_event(
					key,
					true
				)
			);
	}
}

void
sge::x11input::keyboard::device::on_key_release(
	x11input::device::window_event const &_event
)
{
	sge::input::keyboard::key_code::type const key_code(
		x11input::keyboard::translate_key_code(
			x11input::keyboard::key_code_to_key_sym(
				window_->display(),
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
			sge::input::keyboard::key(
				key_code,
				0
			),
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
