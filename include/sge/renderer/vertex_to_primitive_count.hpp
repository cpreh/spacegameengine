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


#ifndef SGE_RENDERER_VERTEX_TO_PRIMITIVE_COUNT_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_TO_PRIMITIVE_COUNT_HPP_INCLUDED

#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex_count.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Calculates how many primitives are described by a number of vertices

The number of vertices given by \a vertices (which could also be indirectly
given by a number of indices) combined with a certain primitive_type given by
\a type describe a certain number of primitives. For example, using the
sge::renderer::primitive_type::triangle_list

\param vertices The number of vertices (or a number of indices used to count
vertices)

\param type The primitive type
*/
SGE_RENDERER_SYMBOL
sge::renderer::primitive_count const
vertex_to_primitive_count(
	sge::renderer::vertex_count vertices,
	sge::renderer::primitive_type::type type
);

}
}

#endif
