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


#ifndef SGE_SPRITE_RENDER_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_OPTIONS_HPP_INCLUDED

#include <sge/sprite/render/geometry_options.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options_fwd.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	sge::sprite::render::geometry_options::type GeometryOptions,
	sge::sprite::render::matrix_options::type MatrixOptions,
	sge::sprite::render::state_options::type StateOptions,
	sge::sprite::render::vertex_options::type VertexOptions
>
struct options
{
	static sge::sprite::render::geometry_options::type const
	geometry_options = GeometryOptions;

	static sge::sprite::render::matrix_options::type const
	matrix_options = MatrixOptions;

	static sge::sprite::render::state_options::type const
	state_options = StateOptions;

	static sge::sprite::render::vertex_options::type const
	vertex_options = VertexOptions;
};

}
}
}

#endif
