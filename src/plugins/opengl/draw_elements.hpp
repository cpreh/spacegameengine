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


#ifndef SGE_OPENGL_DRAW_ELEMENTS_HPP_INCLUDED
#define SGE_OPENGL_DRAW_ELEMENTS_HPP_INCLUDED

#include "context/object_fwd.hpp"
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/vertex_count.hpp>


namespace sge
{
namespace opengl
{

void
draw_elements(
	opengl::context::object &,
	renderer::index_buffer const &,
	renderer::first_vertex,
	renderer::vertex_count,
	renderer::indexed_primitive_type::type,
	renderer::primitive_count,
	renderer::first_index
);

}
}

#endif
