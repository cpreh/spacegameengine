/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/detail/vertex_format.hpp>
#include <sge/sprite/detail/constants.hpp>
#include <sge/math/matrix/basic_impl.hpp>
#include <sge/math/matrix/orthogonal_xy.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>

namespace
{

sge::renderer::vf::dynamic_format const dyn_vertex_fmt(
	sge::renderer::vf::make_dynamic_format<
		sge::sprite::detail::vertex_format
	>()
);

}

sge::renderer::device_ptr const
sge::sprite::system_base::renderer() const
{
	return rend;
}

sge::sprite::system_base::system_base(
	renderer::device_ptr const rend)
:
	rend(rend),
	transform_matrix(
		renderer::matrix_pixel_to_space<
			funit
		>(
			rend->screen_size())),
	projection_matrix(
		math::matrix::orthogonal_xy<funit>())
{}

void sge::sprite::system_base::allocate_buffers(
	std::size_t const num_sprites)
{
	if(vb && vb->size() >= num_sprites * detail::vertices_per_sprite)
		return;

	vb = rend->create_vertex_buffer(
		dyn_vertex_fmt,
		num_sprites * detail::vertices_per_sprite,
		renderer::resource_flags::dynamic);

	ib = rend->create_index_buffer(
		renderer::index::format::i16,
		num_sprites * detail::indices_per_sprite,
		renderer::resource_flags::dynamic);
}

void sge::sprite::system_base::matrices()
{
	rend->transform(transform_matrix);
	rend->projection(projection_matrix);
}

sge::renderer::vertex_buffer_ptr const
sge::sprite::system_base::vertex_buffer() const
{
	return vb;
}

sge::renderer::index_buffer_ptr const
sge::sprite::system_base::index_buffer() const
{
	return ib;
}
