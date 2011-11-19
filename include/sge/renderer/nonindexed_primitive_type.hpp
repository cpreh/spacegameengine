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


#ifndef SGE_RENDERER_NONINDEXED_PRIMITIVE_TYPE_HPP_INCLUDED
#define SGE_RENDERER_NONINDEXED_PRIMITIVE_TYPE_HPP_INCLUDED

namespace sge
{
namespace renderer
{

/**
 * \brief The namespace for the non indexed primitive type enum
*/
namespace nonindexed_primitive_type
{
/**
 * The enum type for non indexed primitive types
*/
enum type
{
	/**
	 * \brief Vertices describe points
	 *
	 * Each vertex describes one point.
	*/
	point,
	/**
	 * \brief Vertices describe lines
	 *
	 * Every two adjacent vertices form one line.
	*/
	line,
	/**
	 * \brief Vertices describe a line strip
	 *
	 * The first two vertices form a line. For every other vertex,
	 * it is combined with the current one to form another line.
	*/
	line_strip,
	/**
	 * \brief Vertices describe triangles
	 *
	 * Every three adjacent vertices form one triangle.
	*/
	triangle,
	/**
	 * \brief Vertices describe a triangle strip
	 *
	 * The first three vertices form a triangle. For every other vertex, it
	 * is combined with the current and the previous one to form another
	 * triangle.
	*/
	triangle_strip,
	/**
	 * \brief Vertices describe a triangle fan
	 *
	 * The first three vertices form a triangle. For every other vertex, it
	 * is combined with the previous and the first vertex to form another
	 * triangle.
	*/
	triangle_fan
};
}

}
}

#endif
