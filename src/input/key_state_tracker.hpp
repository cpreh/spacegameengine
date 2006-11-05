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


#ifndef SGE_KEY_STATE_TRACKER_HPP_INCLUDED
#define SGE_KEY_STATE_TRACKER_HPP_INCLUDED

#include <map>
#include "./input_system.hpp"
#include "./key_type.hpp"
#include "./callback_handle.hpp"

namespace sge
{

class key_state_tracker {
public:
	key_state_tracker(input_system_ptr);
	key_state operator[](const key_code&);
	key_state operator[](const key_type&);
private:
	void event_handler(const key_pair& key);

	typedef std::map<key_code, key_state> key_code_map;
	typedef std::map<key_type, key_state> key_type_map;
	callback_handle _cb;
	key_code_map key_codes;
	key_type_map key_types;
};

}

#endif
