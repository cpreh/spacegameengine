//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PRIMITIVE_TYPE_HPP_INCLUDED
#define SGE_RENDERER_PRIMITIVE_TYPE_HPP_INCLUDED

#include <sge/renderer/primitive_type_fwd.hpp>


namespace sge::renderer
{

/**
\brief Lists all the geometry primitives that can be rendered

\ingroup sge_renderer
*/
enum class primitive_type
{
	/**
	\brief Vertices describe points

	Each vertex defines a point.
	*/
	point_list,
	/**
	\brief Vertices describe lines

	Every two adjacent vertices define a line.
	*/
	line_list,
	/**
	\brief Vertices describe a line strip

	The first two vertices form a line. For every other vertex, it is
	combined with the current one to form another line.
	*/
	line_strip,
	/**
	\brief Indices describe triangles

	Every three adjacent vertices define a triangle.
	*/
	triangle_list,
	/**
	\brief Vertices describe a triangle strip

	The first three vertices form a triangle. For every other vertex, it is
	combined with the current and the previous one to form another
	triangle.
	*/
	triangle_strip,
	/**
	\brief Vertices describe a triangle fan

	The first three vertices form a triangle. For every other vertex, it is
	combined with the previous and the first vertex to form another
	triangle.
	*/
	triangle_fan
};

}

#endif
