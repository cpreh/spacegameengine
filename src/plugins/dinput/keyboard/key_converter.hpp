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


#ifndef SGE_DINPUT_KEYBOARD_KEY_CONVERTER_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_KEY_CONVERTER_HPP_INCLUDED

#include "key_converter_fwd.hpp"
#include "../di.hpp"
#include <sge/input/keyboard/key_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace dinput
{
namespace keyboard
{

class key_converter
{
	FCPPT_NONCOPYABLE(
		key_converter
	);
public:
	key_converter();

	~key_converter();

	input::keyboard::key_code::type
	create_key_code(
		DWORD ofs
	) const;

	DWORD
	create_dik(
		input::keyboard::key_code::type
	) const;
private:
	typedef std::vector<
		input::keyboard::key_code::type
	> key_vector;

	key_vector key_vector_;

	typedef std::map<
		input::keyboard::key_code::type,
		DWORD
	> reverse_map;

	reverse_map reverse_map_;
};

}
}
}

#endif
