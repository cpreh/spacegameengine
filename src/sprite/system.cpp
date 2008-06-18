/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2008       Simon Stienen    (s.stienen@slashlife.org)

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


#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/vertex_format.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/math/matrix_impl.hpp>

const unsigned init_sprites = 25;

sge::sprite::system::system(const renderer::device_ptr rend)
 : default_transformable(
 	rend,
	renderer::matrix_pixel_to_space(rend->screen_size()),
	math::matrix_orthogonal_xy()),
   rend(rend),
   vb(
   	rend->create_vertex_buffer(
		renderer::vertex_format()
			.add(renderer::vertex_usage::pos)
			.add(renderer::vertex_usage::diffuse)
			.add(renderer::vertex_usage::tex),
		init_sprites * detail::vertices_per_sprite,
		renderer::resource_flags::write_only
		| renderer::resource_flags::dynamic)),
  ib(
  	rend->create_index_buffer(
		init_sprites * detail::indices_per_sprite))
{}

const sge::renderer::device_ptr sge::sprite::system::get_renderer() const
{
	return rend;
}
