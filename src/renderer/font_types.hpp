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


#ifndef SGE_FONT_TYPES_HPP_INCLUDED
#define SGE_FONT_TYPES_HPP_INCLUDED

#include <string>
#include "../math/types.hpp"
#include "./types.hpp"

namespace sge
{

enum font_weight {
	FW_Thin, 
	FW_Normal,
	FW_Bold,
	FW_Heavy
};

enum font_flags {
	FTF_AlignLeft    = 1,
	FTF_AlignRight   = 1 << 1,
	FTF_AlignHCenter = 1 << 2,
	FTF_AlignTop     = 1 << 3,
	FTF_AlignVCenter = 1 << 4,
	FTF_AlignBottom  = 1 << 5,
	FTF_NoMultiLine  = 1 << 6,
	FTF_Default      = FTF_AlignLeft | FTF_AlignTop
};
typedef unsigned font_flag_t;

typedef space_unit font_unit;
typedef point font_pos;
typedef dim   font_size;
typedef rect   font_rect;
typedef char font_char;
typedef std::basic_string<font_char> font_string;

}

#endif
