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

#include "types.hpp"
#include "../export.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../math/rect.hpp"

namespace sge
{
namespace sprite
{

SGE_SYMBOL renderer::vertex_buffer::iterator
fill_position(
	renderer::vertex_buffer::iterator it,
	const rect& rs,
	depth_type z);

SGE_SYMBOL renderer::vertex_buffer::iterator
fill_tex_coordinates(
	renderer::vertex_buffer::iterator it,
	const renderer::tex_rect& rt);

SGE_SYMBOL renderer::vertex_buffer::iterator
fill_vertices(
	renderer::vertex_buffer::iterator it,
	const rect& rs,
	const renderer::tex_rect& rt,
	depth_type z);

SGE_SYMBOL renderer::vertex_buffer::iterator
fill_position_rotated(
	renderer::vertex_buffer::iterator it,
	const rect& rbs,
	rotation_type rot,
	const point& center,
	depth_type z);

SGE_SYMBOL renderer::vertex_buffer::iterator
fill_color(
	renderer::vertex_buffer::iterator it,
	color col);

SGE_SYMBOL renderer::index_buffer::iterator
fill_indices(
	renderer::index_buffer::iterator it,
	renderer::index_buffer::value_type start);

}
}

#endif
