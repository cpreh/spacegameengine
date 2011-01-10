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


#include "list.hpp"
#include <sge/input/modifier/filter.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/key.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/foreach.hpp>

sge::input::modifier::filter::filter(
	sge::input::keyboard::device &_keyboard
)
:
	signal_(),
	repeat_signal_(),
	ic_(
		_keyboard.key_callback(
			std::tr1::bind(
				&filter::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	irc_(
		_keyboard.key_repeat_callback(
			std::tr1::bind(
				&filter::input_repeat_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	modifiers_()
{
	BOOST_FOREACH(
		object const &o,
		list()
	)
		BOOST_FOREACH(
			keyboard::key_code::type const &c,
			o.codes
		)
			modifiers_.insert(
				c,
				false
			);
}

fcppt::signal::auto_connection
sge::input::modifier::filter::register_callback(
	callback_type const &_function
)
{
	return
		signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
sge::input::modifier::filter::register_repeat_callback(
	repeat_callback_type const &_function
)
{
	return
		repeat_signal_.connect(
			_function
		);
}

sge::input::modifier::filter::~filter()
{}

void
sge::input::modifier::filter::input_callback(
	keyboard::key_event const &_key
)
{
	BOOST_FOREACH(
		object const &o,
		list()
	)
	{
		BOOST_FOREACH(
			keyboard::key_code::type const &c,
			o.codes
		)
		{
			if (c == _key.key().code())
			{
				modifiers_[
					_key.key().code()
				] = _key.pressed();

				return;
			}
		}
	}

	signal_(
		_key,
		modifiers_
	);
}

void
sge::input::modifier::filter::input_repeat_callback(
	keyboard::key_repeat_event const &_key
)
{
	repeat_signal_(
		_key,
		modifiers_
	);
}
