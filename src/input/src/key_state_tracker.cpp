/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <boost/bind.hpp>
#include "../key_state_tracker.hpp"

sge::key_state_tracker::key_state_tracker(const input_system_ptr is)
 : _cb(is->register_callback(boost::bind(&key_state_tracker::event_handler,this,_1)))
{}

sge::key_state sge::key_state_tracker::operator[](const key_code& c)
{
	return key_codes[c];
}

sge::key_state sge::key_state_tracker::operator[](const key_type& c)
{
	return key_types[c];
}

void sge::key_state_tracker::event_handler(const key_pair& key)
{
	key_codes[key.first.code] = key.second;
	key_types[key.first] = key.second;
}
