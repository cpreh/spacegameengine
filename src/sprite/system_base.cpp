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


#include <sge/sprite/system_base.hpp>
#include <sge/sprite/types.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/math/matrix_util.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/renderer/vertex_format.hpp>
#include <sge/renderer/vertex_buffer_util.hpp>
#include <sge/renderer/index_buffer_util.hpp>

namespace
{

unsigned const init_sprites = 25;

}

sge::renderer::device_ptr const
sge::sprite::system_base::get_renderer() const
{
	return rend;
}

sge::sprite::system_base::system_base(
	renderer::device_ptr const rend)
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
		renderer::resource_flags::dynamic)),
  ib(
  	rend->create_index_buffer(
		renderer::index_format::index16,
		init_sprites * detail::indices_per_sprite,
		renderer::resource_flags::dynamic))
{}

void sge::sprite::system_base::allocate_buffers(
	std::size_t const num_sprites)
{
	if(vb->size() >= num_sprites * detail::vertices_per_sprite)
		return;

	vb = renderer::resize(
		vb,
		rend,
		num_sprites * detail::vertices_per_sprite);
	ib = renderer::resize(
		ib,
		rend,
		num_sprites * detail::indices_per_sprite);
}

sge::renderer::vertex_buffer_ptr const
sge::sprite::system_base::get_vertex_buffer() const
{
	return vb;
}

sge::renderer::index_buffer_ptr const
sge::sprite::system_base::get_index_buffer() const
{
	return ib;
}
