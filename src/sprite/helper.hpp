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


#ifndef SGE_SPRITE_HELDER_HPP_INCLUDED
#define SGE_SPRITE_HELDER_HPP_INCLUDED

#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../math/rect.hpp"
#include "types.hpp"

namespace sge
{

vertex_buffer::iterator fill_sprite_position(vertex_buffer::iterator it,
                                             const sprite_rect& rs,
                                             sprite_depth_type z);

vertex_buffer::iterator fill_sprite_tex_coordinates(vertex_buffer::iterator it,
                                                    const tex_rect& rt);

vertex_buffer::iterator fill_sprite_vertices(vertex_buffer::iterator it,
                                             const sprite_rect& rs,
                                             const tex_rect& rt,
                                             sprite_depth_type z);

vertex_buffer::iterator fill_sprite_position_rotated(vertex_buffer::iterator it,
                                                     const sprite_rect& rbs,
                                                     sprite_rotation_type rot,
                                                     const sprite_point& center,
                                                     sprite_depth_type z);

vertex_buffer::iterator fill_sprite_color(vertex_buffer::iterator it,
                                          color col);

index_buffer::iterator fill_sprite_indices(index_buffer::iterator it,
                                           index_buffer::value_type start);

}

#endif
