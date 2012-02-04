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


#ifndef SGE_SPRITE_BUFFERS_WITH_DECLARATION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_WITH_DECLARATION_IMPL_HPP_INCLUDED

#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/sprite/make_vertex_format.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>


template<
	typename Buffers
>
sge::sprite::buffers::with_declaration<
	Buffers
>::with_declaration(
	sge::renderer::device &_device,
	sge::sprite::buffers::option::type const _buffers_option
)
:
	vertex_declaration_(
		_device.create_vertex_declaration(
			sge::sprite::make_vertex_format<
				typename Buffers::choices
			>()
		)
	),
	buffers_(
		sge::sprite::buffers::parameters(
			_device,
			*vertex_declaration_
		),
		_buffers_option
	)
{
}

template<
	typename Buffers
>
sge::sprite::buffers::with_declaration<
	Buffers
>::~with_declaration()
{
}

template<
	typename Buffers
>
typename sge::sprite::buffers::with_declaration<
	Buffers
>::buffers_type &
sge::sprite::buffers::with_declaration<
	Buffers
>::buffers()
{
	return buffers_;
}

template<
	typename Buffers
>
typename sge::sprite::buffers::with_declaration<
	Buffers
>::buffers_type const &
sge::sprite::buffers::with_declaration<
	Buffers
>::buffers() const
{
	return buffers_;
}

template<
	typename Buffers
>
sge::sprite::buffers::parameters const &
sge::sprite::buffers::with_declaration<
	Buffers
>::parameters() const
{
	return buffers_.parameters();
}

template<
	typename Buffers
>
sge::renderer::vertex_declaration const &
sge::sprite::buffers::with_declaration<
	Buffers
>::vertex_declaration() const
{
	return *vertex_declaration_;
}

#endif
