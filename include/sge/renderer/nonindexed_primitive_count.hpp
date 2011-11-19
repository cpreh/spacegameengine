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


#ifndef SGE_RENDERER_NONINDEXED_PRIMITIVE_COUNT_HPP_INCLUDED
#define SGE_RENDERER_NONINDEXED_PRIMITIVE_COUNT_HPP_INCLUDED

#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex_count.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Calculates the number of non indexed primitives
 *
 * Calculates how many non indexed primitives of type \a type will be rendered
 * by \a vertices. Non indexed primitives can either be isolated, like
 * triangles and lines, or they can be connected like triangle strips, line
 * strips and line fans.
 *
 * \note Lines needs a multiple of 2 vertices, triangles need a multiple of 3.
 * line strips need at least two vertices, triangle strips and fans need at
 * least 3.
 *
 * \param vertices The number of vertices that will be used
 * \param type The non indexed primitive type
 *
 * \return The number of primitives
 *
 * \throw renderer::exception if vertices has an incorrect value
*/
SGE_RENDERER_SYMBOL
renderer::size_type
nonindexed_primitive_count(
	renderer::vertex_count vertices,
	renderer::nonindexed_primitive_type::type type
);

}
}

#endif
