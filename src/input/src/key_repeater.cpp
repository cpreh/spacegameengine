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


#include "../key_repeater.hpp"
#include <boost/bind.hpp>

sge::key_repeater::key_repeater(const input_system_ptr is, const timer::interval_type interval, const timer::interval_type repeat_time)
 : last_key(no_key),
   interval_t(interval),
   repeat_t(repeat_time)
{
	is->register_callback(boost::bind(&key_repeater::key_callback, this, _1));
}

void sge::key_repeater::key_callback(const key_pair& p)
{
	if(!is_keyboard_key(p.first.code)
	   || is_shift(p.first.code))
		return;

	if(static_cast<bool>(p.second) == false)
	{
		if(p.first == last_key)
			repeat_timer().deactivate();
		return;
	}
	else
		repeat_timer().activate();
	
	if(p.first != last_key)
		repeat_timer().reset();

	last_key = p.first;
}

sge::key_type sge::key_repeater::repeated_key()
{
	if(repeat_timer().expired() && interval_timer().update())
		return last_key;
	return no_key;
}

sge::timer& sge::key_repeater::interval_timer()
{
	return interval_t;
}

sge::timer& sge::key_repeater::repeat_timer()
{
	return repeat_t;
}

const sge::key_type sge::key_repeater::no_key("");
