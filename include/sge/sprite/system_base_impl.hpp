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


#ifndef SGE_SPRITE_SYSTEM_BASE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_BASE_IMPL_HPP_INCLUDED

#include <sge/sprite/system_base_decl.hpp>
#include <sge/sprite/detail/vertex_format.hpp>
#include <sge/sprite/detail/vertices_per_sprite.hpp>
#include <sge/sprite/detail/indices_per_sprite.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/orthogonal_xy.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>

template<
	typename Choices
>
sge::renderer::device_ptr const
sge::sprite::system_base<Choices>::renderer() const
{
	return rend;
}

template<
	typename Choices
>
void
sge::sprite::system_base<Choices>::transform(
	matrix const &ntransform_matrix
)
{
	additional_transform_ = ntransform_matrix;
}

template<
	typename Choices
>
typename sge::sprite::system_base<Choices>::matrix const &
sge::sprite::system_base<Choices>::transform() const
{
	return additional_transform_;
}

template<
	typename Choices
>
void
sge::sprite::system_base<Choices>::matrices()
{
	rend->transform(
		renderer::matrix_mode::world,
		additional_transform_
		* transform_matrix
	);

	rend->transform(
		renderer::matrix_mode::projection,
		projection_matrix
	);
}

template<
	typename Choices
>
sge::sprite::system_base<Choices>::system_base(
	renderer::device_ptr const rend
)
:
	rend(rend),
	transform_matrix(
		renderer::matrix_pixel_to_space<
			typename Choices::type_choices::float_type
		>(
			rend->screen_size()
		)
	),
	projection_matrix(
		fcppt::math::matrix::orthogonal_xy<
			typename Choices::type_choices::float_type
		>()
	),
	additional_transform_(
		matrix::identity()
	),
	vb(),
	ib()
{}

template<
	typename Choices
>
sge::sprite::system_base<Choices>::~system_base()
{}

template<
	typename Choices
>
void
sge::sprite::system_base<Choices>::allocate_buffers(
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
		renderer::index::dynamic::format::i16,
		num_sprites * detail::indices_per_sprite,
		renderer::resource_flags::dynamic
	);
}

template<
	typename Choices
>
sge::renderer::vertex_buffer_ptr const
sge::sprite::system_base<Choices>::vertex_buffer() const
{
	return vb;
}

template<
	typename Choices
>
sge::renderer::index_buffer_ptr const
sge::sprite::system_base<Choices>::index_buffer() const
{
	return ib;
}

template<
	typename Choices
>
sge::renderer::vf::dynamic::format const
sge::sprite::system_base<Choices>::dyn_vertex_fmt(
	sge::renderer::vf::dynamic::make_format<
		typename sge::sprite::detail::vertex_format<
			Choices
		>::type
	>()
);

#endif
