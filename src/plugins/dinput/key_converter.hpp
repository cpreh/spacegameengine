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


#ifndef SGE_DINPUT_KEY_CONVERTER_HPP_INCLUDED
#define SGE_DINPUT_KEY_CONVERTER_HPP_INCLUDED

#include "di.hpp"
#include <sge/input/key_type.hpp>
#include <vector>
#include <map>

namespace sge
{
namespace dinput
{

class key_converter {
public:
	key_converter();
	input::key_code create_key_code(DWORD ofs) const;
	DWORD   create_dik(input::key_code key) const;
private:
	typedef std::vector<input::key_code> key_vector;
	key_vector v;
	std::map<input::key_code, DWORD> vr;
};

}
}

#endif
