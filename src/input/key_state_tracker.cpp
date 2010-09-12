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
	system_ptr const _sys
)
:
	con_(
		_sys->register_callback(
			std::tr1::bind(
				&key_state_tracker::event_handler,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	key_codes_()
{}

sge::input::key_state
sge::input::key_state_tracker::state(
	key_code const _code
)
{
	return key_codes_[_code];
}

sge::input::key_state
sge::input::key_state_tracker::operator[](
	key_code const _code
)
{
	return state(_code);
}

void
sge::input::key_state_tracker::event_handler(
	key_pair const &_pair
)
{
	key_codes_[
		_pair.key().code()
	] = _pair.value();
}
