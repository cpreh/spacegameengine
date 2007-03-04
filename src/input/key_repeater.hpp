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


#ifndef SGE_KEY_REPEATER_HPP_INCLUDED
#define SGE_KEY_REPEATER_HPP_INCLUDED

#include <boost/signals/trackable.hpp>
#include "../timer.hpp"
#include "key_type.hpp"
#include "input_system.hpp"

namespace sge
{

class key_repeater : boost::signals::trackable {
public:
	key_repeater(input_system_ptr is, timer::interval_type interval, timer::interval_type repeat_time);
	key_type repeated_key();
	static const key_type no_key;
	timer& interval_timer();
	timer& repeat_timer();
private:
	void key_callback(const key_pair&);

	key_type last_key;
	timer interval_t,
	      repeat_t;
};

}

#endif
