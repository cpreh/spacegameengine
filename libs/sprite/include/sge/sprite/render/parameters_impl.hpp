/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_RENDER_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/render/parameters_decl.hpp>


template<
	typename StateOptions
>
sge::sprite::render::parameters<
	StateOptions
>::parameters(
	render_context_type &_render_context,
	sge::renderer::vertex::declaration const &_vertex_declaration
)
:
	render_context_(
		_render_context
	),
	vertex_declaration_(
		_vertex_declaration
	)
{
}

template<
	typename StateOptions
>
typename
sge::sprite::render::parameters<
	StateOptions
>::render_context_type &
sge::sprite::render::parameters<
	StateOptions
>::render_context() const
{
	return
		render_context_.get();
}

template<
	typename StateOptions
>
sge::renderer::vertex::declaration const &
sge::sprite::render::parameters<
	StateOptions
>::vertex_declaration() const
{
	return
		vertex_declaration_.get();
}

#endif
