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


#ifndef SGE_SPRITE_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/sprite/buffers_impl.hpp>
#include <sge/sprite/buffers_option.hpp>
#include <sge/sprite/make_vertex_format.hpp>
#include <sge/sprite/system_decl.hpp>


template<
	typename Choices
>
sge::sprite::system<
	Choices
>::system(
	sge::renderer::device &_device,
	sge::sprite::buffers_option::type const _buffers_option
)
:
	vertex_declaration_(
		_device.create_vertex_declaration(
			sge::sprite::make_vertex_format<
				Choices
			>()
		)
	),
	buffers_(
		_device,
		*vertex_declaration_,
		_buffers_option
	)
{
}

template<
	typename Choices
>
sge::sprite::system<
	Choices
>::~system()
{
}

template<
	typename Choices
>
typename sge::sprite::system<
	Choices
>::buffers_type &
sge::sprite::system<
	Choices
>::buffers()
{
	return buffers_;
}

template<
	typename Choices
>
typename sge::sprite::system<
	Choices
>::buffers_type const &
sge::sprite::system<
	Choices
>::buffers() const
{
	return buffers_;
}

#endif
