/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>

sge::input::modifier::filter::filter(
	sge::input::system_ptr const is
)
:
	signal(),
	repeat_signal(),
	ic(
		is->register_callback(
			std::tr1::bind(
				&filter::input_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	irc(
		is->register_repeat_callback(
			std::tr1::bind(
				&filter::input_repeat_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	modifiers()
{
	BOOST_FOREACH(
		object const &o,
		list()
	)
		BOOST_FOREACH(
			key_code const &c,
			o.codes
		)
			modifiers.insert(
				c,
				static_cast<key_state>(0)
			);
}

fcppt::signal::auto_connection
sge::input::modifier::filter::register_callback(
	callback_type const &f
)
{
	return signal.connect(f);
}

fcppt::signal::auto_connection
sge::input::modifier::filter::register_repeat_callback(
	repeat_callback_type const &f
)
{
	return repeat_signal.connect(f);
}

sge::input::modifier::filter::~filter()
{}

void
sge::input::modifier::filter::input_callback(
	key_pair const &k
)
{
	BOOST_FOREACH(
		object const &o,
		list()
	)
	{
		BOOST_FOREACH(
			key_code const &c,
			o.codes
		)
		{
			if (c == k.key().code())
			{
				modifiers[k.key().code()] = k.value();
				return;
			}
		}
	}

	signal(k,modifiers);
}

void
sge::input::modifier::filter::input_repeat_callback(
	key_type const &k
)
{
	repeat_signal(k,modifiers);
}
