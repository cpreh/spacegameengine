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


#include "../keyboard_keys.hpp"
#include "../key_vector.hpp"
#include "../looked_up_string.hpp"
#include <sge/input/keyboard/key.hpp>
#include <boost/foreach.hpp>

sge::x11input::key_vector const
sge::x11input::keyboard_keys(
	x11input::looked_up_string const &_string
)
{
	if(
		_string.char_codes().empty()
	)
		return
			x11input::key_vector(
				1u,
				sge::input::keyboard::key(
					_string.key_code(),
					0
				)
			);

	x11input::key_vector ret;

	BOOST_FOREACH(	
		x11input::char_vector::const_reference code,
		_string.char_codes()
	)
		ret.push_back(
			sge::input::keyboard::key(
				_string.key_code(),
				code
			)
		);
	
	return ret;
}
