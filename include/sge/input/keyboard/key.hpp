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


#ifndef SGE_INPUT_KEYBOARD_KEY_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_KEY_HPP_INCLUDED

#include <sge/input/keyboard/key_fwd.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/char_type.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace input
{
namespace keyboard
{

class key
{
public:
	SGE_SYMBOL
	key(
		key_code::type,
		keyboard::char_type
	);

	SGE_SYMBOL
	key_code::type
	code() const;

	SGE_SYMBOL
	keyboard::char_type
	character() const;
private:
	key_code::type code_;

	keyboard::char_type character_;
};

SGE_SYMBOL
bool
operator==(
	keyboard::key const &,
	keyboard::key const &
);

SGE_SYMBOL
bool
operator!=(
	keyboard::key const &,
	keyboard::key const &
);

}
}
}

#endif
