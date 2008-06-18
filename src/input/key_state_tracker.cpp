/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <boost/bind.hpp>

sge::input::key_state_tracker::key_state_tracker(
	const system_ptr is)
: con(
	is->register_callback(
		boost::bind(
			&key_state_tracker::event_handler,
			this,
			_1)))
{}

sge::input::key_state
sge::input::key_state_tracker::state(const key_code& c)
{
	return key_codes[c];
}

sge::input::key_state
sge::input::key_state_tracker::state(const key_type& c)
{
	return key_types[c];
}

sge::input::key_state
sge::input::key_state_tracker::state(const key_type::char_type& c)
{
	return key_chars[c];
}

sge::input::key_state
sge::input::key_state_tracker::operator[](const key_code&k)
{
	return state(k);
}

sge::input::key_state
sge::input::key_state_tracker::operator[](const key_type&k)
{
	return state(k);
}

sge::input::key_state
sge::input::key_state_tracker::operator[](const key_type::char_type&k)
{
	return state(k);
}

void sge::input::key_state_tracker::event_handler(const key_pair& pair)
{
	const key_type key = pair.key();
	key_codes[key.code()] = key_types[key] = key_chars[key.char_code()] = pair.value();
}
