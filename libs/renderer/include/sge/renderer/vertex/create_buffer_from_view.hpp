//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VIEW_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
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
SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::vertex::buffer_unique_ptr
create_buffer_from_view(
	sge::renderer::device::core_ref device,
	sge::renderer::vertex::const_declaration_ref vertex_declaration,
	sge::renderer::vf::dynamic::const_view const &view,
	sge::renderer::resource_flags_field const &flags
);

}
}
}

#endif
