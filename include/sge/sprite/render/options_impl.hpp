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


#ifndef SGE_SPRITE_RENDER_OPTIONS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_OPTIONS_IMPL_HPP_INCLUDED

#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options_decl.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>


inline
sge::sprite::render::options::options(
	sge::sprite::render::matrix_options::type const _matrix_options,
	sge::sprite::render::state_options::type const _state_options,
	sge::sprite::render::vertex_options::type const _vertex_options
)
:
	matrix_options_(
		_matrix_options
	),
	state_options_(
		_state_options
	),
	vertex_options_(
		_vertex_options
	)
{
}

inline
sge::sprite::render::matrix_options::type
sge::sprite::render::options::matrix_options() const
{
	return matrix_options_;
}

inline
sge::sprite::render::state_options::type
sge::sprite::render::options::state_options() const
{
	return state_options_;
}

inline
sge::sprite::render::vertex_options::type
sge::sprite::render::options::vertex_options() const
{
	return vertex_options_;
}

#endif
