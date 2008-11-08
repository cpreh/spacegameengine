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

#include "../renderer/any_color.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"
#include "../math/rect.hpp"
#include "../math/matrix.hpp"
#include "../math/circle.hpp"

// TODO: split this bloated header

namespace sge
{
namespace sprite
{

typedef float                       funit;
typedef int                         unit;
typedef math::vector<unit, 2> point;
typedef math::basic_dim<unit, 2>    dim;
typedef math::basic_rect<unit>      rect;
typedef renderer::any_color         color;
typedef funit                       depth_type;
typedef funit                       rotation_type;
typedef funit                       repetition_type;
typedef math::matrix<funit, 4, 4> matrix;

typedef math::basic_rect<
	funit
> tex_rect;

typedef math::vector<
	funit,
	3
> pos3;

typedef math::vector<
	funit,
	2
> pos2;

typedef math::basic_circle<
	funit
> circle;

typedef pos2 tex_pos;

namespace detail
{

unsigned const indices_per_sprite = 6,
               vertices_per_sprite = 4;
}

}
}

#endif
