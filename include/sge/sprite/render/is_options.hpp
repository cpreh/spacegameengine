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


#ifndef SGE_SPRITE_RENDER_IS_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_IS_OPTIONS_HPP_INCLUDED

#include <sge/sprite/render/geometry_options.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <sge/sprite/render/options_fwd.hpp>
#include <sge/sprite/render/state_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename T
>
struct is_options
:
boost::mpl::false_
{
};

template<
	sge::sprite::render::geometry_options::type GeometryOptions,
	sge::sprite::render::matrix_options::type MatrixOptions,
	sge::sprite::render::state_options::type StateOptions,
	sge::sprite::render::vertex_options::type VertexOptions
>
struct is_options<
	sge::sprite::render::options<
		GeometryOptions,
		MatrixOptions,
		StateOptions,
		VertexOptions
	>
>
:
boost::mpl::true_
{
};

}
}
}

#endif
