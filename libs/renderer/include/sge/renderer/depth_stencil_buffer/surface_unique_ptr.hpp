//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/depth_stencil_buffer/surface_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace renderer
{
namespace depth_stencil_buffer
{

/**
\brief A unique pointer to an sge::renderer::depth_stencil_buffer::surface
*/
using
surface_unique_ptr
=
fcppt::unique_ptr<
	sge::renderer::depth_stencil_buffer::surface
>;

}
}
}

#endif
