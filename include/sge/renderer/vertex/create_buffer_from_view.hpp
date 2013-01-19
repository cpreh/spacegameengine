/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VIEW_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/const_view_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief Creates a vertex buffer copied from a view

Creates a vertex buffer copied from \a view with vertex declaration \a
vertex_declaration and resource flags \a flags.

\param device The device to create the vertex buffer from

\param vertex_declaration The vertex declaration the buffer will be created for

\param view The view to copy into the vertex buffer

\param flags The resource flags for the vertex buffer

\return A unique ptr to the created vertex buffer

\throw Anything that sge::renderer::device::create_vertex_buffer throws

\warning The behaviour is undefined if \a view doesn't belong to \a
vertex_declaration
*/
SGE_RENDERER_SYMBOL
sge::renderer::vertex::buffer_unique_ptr
create_buffer_from_view(
	sge::renderer::device::core &device,
	sge::renderer::vertex::declaration &vertex_declaration,
	sge::renderer::vf::dynamic::const_view const &view,
	sge::renderer::resource_flags_field const &flags
);

}
}
}

#endif
