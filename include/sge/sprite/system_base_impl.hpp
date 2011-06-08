/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/detail/allocate_buffers.hpp>
#include <sge/sprite/detail/vertex_format.hpp>
#include <sge/sprite/detail/vertices_per_sprite.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/device.hpp>

template<
	typename Choices
>
sge::renderer::device &
sge::sprite::system_base<Choices>::renderer() const
{
	return renderer_;
}

template<
	typename Choices
>
sge::renderer::vertex_declaration const &
sge::sprite::system_base<Choices>::vertex_declaration() const
{
	return *vertex_declaration_;
}

template<
	typename Choices
>
sge::sprite::system_base<Choices>::system_base(
	renderer::device &_renderer
)
:
	renderer_(_renderer),
	vertex_declaration_(
		_renderer.create_vertex_declaration(
			dyn_vertex_fmt_
		)
	),
	buffers_()
{
}

template<
	typename Choices
>
sge::sprite::system_base<Choices>::~system_base()
{
}

template<
	typename Choices
>
void
sge::sprite::system_base<Choices>::allocate_buffers(
	sge::renderer::size_type const _num_sprites
)
{
	if(
		this->vertex_buffer()
		&& this->vertex_buffer()->size()
		>= _num_sprites
		*
		detail::vertices_per_sprite<
		 	typename Choices::elements
		>::value
	)
		return;

	detail::allocate_buffers<
		typename Choices::elements
	>(
		renderer_,
		*vertex_declaration_,
		_num_sprites,
		buffers_
	);
}

template<
	typename Choices
>
sge::renderer::vertex_buffer *
sge::sprite::system_base<Choices>::vertex_buffer()
{
	return
		buffers_. template get<
			detail::roles::vertex_buffer
		>().get();
}

template<
	typename Choices
>
sge::renderer::index_buffer *
sge::sprite::system_base<Choices>::index_buffer()
{
	return
		buffers_. template get<
			detail::roles::index_buffer
		>().get();
}

template<
	typename Choices
>
typename sge::sprite::system_base<Choices>::buffers_type const &
sge::sprite::system_base<Choices>::buffers() const
{
	return buffers_;
}

template<
	typename Choices
>
sge::renderer::vf::dynamic::format const
sge::sprite::system_base<Choices>::dyn_vertex_fmt_(
	sge::renderer::vf::dynamic::make_format<
		typename sge::sprite::detail::vertex_format<
			Choices
		>::type
	>()
);

#endif
