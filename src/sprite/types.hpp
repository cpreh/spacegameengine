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


#ifndef SGE_SPRITE_TYPES_HPP_INCLUDED
#define SGE_SPRITE_TYPES_HPP_INCLUDED

#include "../types.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"

namespace sge
{

typedef space_unit                         sprite_unit;
typedef math::basic_vector<sprite_unit, 2> sprite_point;
typedef math::basic_dim<sprite_unit, 2>    sprite_dim;
typedef math::basic_rect<sprite_unit>      sprite_rect;
typedef space_unit                         sprite_depth_type;
typedef space_unit                         sprite_rotation_type;
typedef space_unit                         sprite_repetition_type;

}

#endif
