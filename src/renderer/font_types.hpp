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

#include "color.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"
#include "../math/rect.hpp"
#include "../string.hpp"

namespace sge
{

typedef int                         font_unit;
typedef font_unit                   font_size;
typedef math::vector<font_unit,2>   font_pos;
typedef math::dim<font_size,2>      font_dim;
typedef color_element               font_color;
typedef math::basic_rect<font_unit> font_rect;
typedef string::value_type          font_char;

}

#endif
