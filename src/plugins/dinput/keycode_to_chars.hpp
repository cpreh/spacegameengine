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


#ifndef SGE_DINPUT_KEYCODE_TO_CHAR_HPP_INCLUDED
#define SGE_DINPUT_KEYCODE_TO_CHAR_HPP_INCLUDED

#include "char_vector.hpp"
#include "di.hpp"
#include "key_converter_fwd.hpp"
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/mod_state.hpp>

namespace sge
{
namespace dinput
{

sge::dinput::char_vector const
keycode_to_chars(
	sge::input::keyboard::key_code::type,
	sge::input::keyboard::mod_state const &,
	dinput::key_converter const &,
	HKL
);

}
}

#endif
