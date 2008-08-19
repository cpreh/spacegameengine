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
#include "../renderer/vertex_iterator.hpp"
#include "../renderer/index_view.hpp"
#include "../math/rect.hpp"

namespace sge
{
namespace sprite
{

typedef renderer::index_view_16 index_view;

SGE_SYMBOL renderer::vertex_iterator
fill_position(
	renderer::vertex_iterator it,
	const rect& rs,
	depth_type z);

SGE_SYMBOL renderer::vertex_iterator
fill_tex_coordinates(
	renderer::vertex_iterator it,
	const renderer::tex_rect& rt);

SGE_SYMBOL renderer::vertex_iterator
fill_vertices(
	renderer::vertex_iterator it,
	const rect& rs,
	const renderer::tex_rect& rt,
	depth_type z);

SGE_SYMBOL renderer::vertex_iterator
fill_position_rotated(
	renderer::vertex_iterator it,
	const rect& rbs,
	rotation_type rot,
	const point& center,
	depth_type z);

SGE_SYMBOL renderer::vertex_iterator
fill_color(
	renderer::vertex_iterator it,
	color col);

SGE_SYMBOL index_view::iterator
fill_indices(
	index_view::iterator it,
	index_view::value_type start);

}
}

#endif
