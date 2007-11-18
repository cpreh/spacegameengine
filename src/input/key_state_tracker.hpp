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


#ifndef SGE_KEY_STATE_TRACKER_HPP_INCLUDED
#define SGE_KEY_STATE_TRACKER_HPP_INCLUDED

#include <map>
#include <boost/noncopyable.hpp>
#include "../scoped_connection.hpp"
#include "input_system.hpp"
#include "key_type.hpp"

namespace sge
{

class key_state_tracker : boost::noncopyable {
public:
	key_state_tracker(input_system_ptr);
	key_state operator[](const key_code&);
	key_state operator[](const key_type&);
	key_state operator[](const key_type::char_type&);
	bool zero(const key_code&);
	bool zero(const key_type&);
	bool zero(const key_type::char_type&);
private:
	void event_handler(const key_pair& key);
	scoped_connection con;

	typedef std::map<key_code, key_state> key_code_map;
	typedef std::map<key_type, key_state> key_type_map;
	typedef std::map<key_type::char_type, key_state> key_char_map;
	key_code_map key_codes;
	key_type_map key_types;
	key_char_map key_chars;
};

}

#endif
