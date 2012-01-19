/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_BUFFERS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_IMPL_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/sprite/buffers_decl.hpp>
#include <sge/sprite/buffers_option.hpp>
#include <sge/sprite/buffers_option_to_resource_flags.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/detail/buffers/allocate.hpp>
#include <sge/sprite/detail/geometry/vertices_per_sprite.hpp>


template<
	typename Choices
>
sge::sprite::buffers<
	Choices
>::buffers(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vertex_declaration,
	sge::sprite::buffers_option::type const _buffers_option
)
:
	renderer_(
		_renderer
	),
	vertex_declaration_(
		_vertex_declaration
	),
	buffers_option_(
		_buffers_option
	),
	buffers_()
{
}

template<
	typename Choices
>
sge::sprite::buffers<Choices>::~buffers()
{
}

template<
	typename Choices
>
void
sge::sprite::buffers<
	Choices
>::allocate(
	sge::sprite::count const _num_sprites
)
{
	sge::renderer::vertex_buffer *const vb(
		buffers_. template get<
			sge::sprite::detail::roles::vertex_buffer
		>().get()
	);

	if(
		vb
		&& vb->size().get()
		>=
		_num_sprites.get()
		*
		sge::sprite::detail::geometry::vertices_per_sprite<
		 	Choices
		>::value
	)
		return;

	sge::sprite::detail::buffers::allocate<
		Choices
	>(
		renderer_,
		vertex_declaration_,
		_num_sprites,
		buffers_,
		sge::sprite::buffers_option_to_resource_flags(
			buffers_option_
		)
	);
}

template<
	typename Choices
>
sge::renderer::vertex_buffer &
sge::sprite::buffers<
	Choices
>::vertex_buffer()
{
	return
		*buffers_. template get<
			detail::roles::vertex_buffer
		>().get();
}

template<
	typename Choices
>
sge::renderer::index_buffer &
sge::sprite::buffers<
	Choices
>::index_buffer()
{
	return
		*buffers_. template get<
			detail::roles::index_buffer
		>().get();
}

template<
	typename Choices
>
sge::renderer::vertex_buffer const &
sge::sprite::buffers<
	Choices
>::vertex_buffer() const
{
	return
		*buffers_. template get<
			detail::roles::vertex_buffer
		>().get();
}

template<
	typename Choices
>
sge::renderer::index_buffer const &
sge::sprite::buffers<
	Choices
>::index_buffer() const
{
	return
		*buffers_. template get<
			detail::roles::index_buffer
		>().get();
}

template<
	typename Choices
>
sge::renderer::device &
sge::sprite::buffers<
	Choices
>::renderer() const
{
	return renderer_;
}

template<
	typename Choices
>
sge::renderer::vertex_declaration const &
sge::sprite::buffers<
	Choices
>::vertex_declaration() const
{
	return vertex_declaration_;
}

#endif
