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


#ifndef SGE_DINPUT_KEY_CONVERTER_HPP_INCLUDED
#define SGE_DINPUT_KEY_CONVERTER_HPP_INCLUDED

#include <vector>
#include <map>
#include "../../core/input/key_type.hpp"
#include "./di.hpp"

namespace sge
{
	namespace dinput
	{
		class key_converter {
		public:
			key_converter();
			key_code create_key_code(DWORD ofs) const;
			DWORD   create_dik(key_code key) const;
		private:
			std::vector<key_code> v;
			std::map<key_code, DWORD> vr;
		};
	}
}

#endif
