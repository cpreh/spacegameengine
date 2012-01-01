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


#ifndef SGE_RENDERER_VERTEX_BUFFER_TYPES_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_TYPES_HPP_INCLUDED

#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vf/dynamic/const_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/view_fwd.hpp>

namespace sge
{
namespace renderer
{

/**
 * \brief Typedef helper for types used by a vertex buffer
*/
struct vertex_buffer_types
{
	/**
	 * \brief The view type returned when locking the buffer readonly
	*/
	typedef vf::dynamic::const_view const_view_type;

	/**
	 * \brief The view type returned when locking the buffer
	*/
	typedef vf::dynamic::view view_type;

	/**
	 * \brief The offset type
	 *
	 * Describes a starting position in the buffer
	*/
	typedef renderer::first_vertex first_type;

	/**
	 * \brief The count type
	 *
	 * Describes a number of vertices
	*/
	typedef renderer::vertex_count count_type;
};

}
}

#endif
