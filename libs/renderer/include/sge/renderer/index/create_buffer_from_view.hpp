//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_CREATE_BUFFER_FROM_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CREATE_BUFFER_FROM_VIEW_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/dynamic/const_view_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

/**
\brief Creates an index buffer copied from a view

Creates an index buffer copied from \a view with resource flags \a flags.

\param device The device to create the index buffer from

\param view The view to copy into the index buffer

\param flags The resource flags for the index buffer

\return A unique ptr to the created index buffer

\throw Anything that sge::renderer::device::create_index_buffer throws
*/
SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::index::buffer_unique_ptr
create_buffer_from_view(
	sge::renderer::device::core_ref device,
	sge::renderer::index::dynamic::const_view const &view,
	sge::renderer::resource_flags_field const &flags
);

}
}
}

#endif
