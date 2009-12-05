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
#include <sge/sprite/detail/vertices_per_sprite.hpp>
#include <sge/sprite/detail/indices_per_sprite.hpp>
#include <sge/math/matrix/basic_impl.hpp>
#include <sge/math/matrix/orthogonal_xy.hpp>
#include <sge/math/matrix/arithmetic.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <sge/container/bitfield/basic_impl.hpp>

template<
	typename Choices,
	typename Elements
>
sge::renderer::device_ptr const
sge::sprite::system_base<Choices, Elements>::renderer() const
{
	return rend;
}

template<
	typename Choices,
	typename Elements
>
void
sge::sprite::system_base<Choices, Elements>::transform(
	matrix const &ntransform_matrix
)
{
	additional_transform_ = ntransform_matrix;
}

template<
	typename Choices,
	typename Elements
>
sge::sprite::system_base<Choices, Elements>::system_base(
	renderer::device_ptr const rend
)
:
	rend(rend),
	transform_matrix(
		renderer::matrix_pixel_to_space<
			typename Choices::float_type
		>(
			rend->screen_size()
		)
	),
	projection_matrix(
		math::matrix::orthogonal_xy<
			typename Choices::float_type
		>()
	),
	additional_transform_(
		matrix::identity()
	),
	vb(),
	ib()
{}

template<
	typename Choices,
	typename Elements
>
void
sge::sprite::system_base<Choices, Elements>::allocate_buffers(
	sge::renderer::size_type const num_sprites
)
{
	if(vb && vb->size() >= num_sprites * detail::vertices_per_sprite)
		return;

	vb = rend->create_vertex_buffer(
		dyn_vertex_fmt,
		num_sprites * detail::vertices_per_sprite,
		renderer::resource_flags::dynamic
	);

	ib = rend->create_index_buffer(
		renderer::index::format::i16,
		num_sprites * detail::indices_per_sprite,
		renderer::resource_flags::dynamic
	);
}

template<
	typename Choices,
	typename Elements
>
void
sge::sprite::system_base<Choices, Elements>::matrices()
{
	rend->transform(
		additional_transform_
		* transform_matrix
	);

	rend->projection(
		projection_matrix
	);
}

template<
	typename Choices,
	typename Elements
>
sge::renderer::vertex_buffer_ptr const
sge::sprite::system_base<Choices, Elements>::vertex_buffer() const
{
	return vb;
}

template<
	typename Choices,
	typename Elements
>
sge::renderer::index_buffer_ptr const
sge::sprite::system_base<Choices, Elements>::index_buffer() const
{
	return ib;
}

template<
	typename Choices,
	typename Elements
>
sge::renderer::vf::dynamic_format const
sge::sprite::system_base<Choices, Elements>::dyn_vertex_fmt(
	sge::renderer::vf::make_dynamic_format<
		typename sge::sprite::detail::vertex_format<
			Choices,
			Elements
		>::type
	>()
);
