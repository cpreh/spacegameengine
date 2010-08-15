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


#include <sge/input/key_state_tracker.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <fcppt/tr1/functional.hpp>

sge::input::key_state_tracker::key_state_tracker(
	system_ptr const is
)
:
	con(
		is->register_callback(
			std::tr1::bind(
				&key_state_tracker::event_handler,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{}

sge::input::key_state
sge::input::key_state_tracker::state(
	key_code const c
)
{
	return key_codes[c];
}

sge::input::key_state
sge::input::key_state_tracker::state(
	key_type const &c
)
{
	return key_types[c];
}

sge::input::key_state
sge::input::key_state_tracker::operator[](
	key_code const k
)
{
	return state(k);
}

sge::input::key_state
sge::input::key_state_tracker::operator[](
	key_type const &k
)
{
	return state(k);
}

void
sge::input::key_state_tracker::event_handler(
	key_pair const &pair
)
{
	key_type const key = pair.key();

	key_codes[key.code()] = key_types[key] = pair.value();
}
