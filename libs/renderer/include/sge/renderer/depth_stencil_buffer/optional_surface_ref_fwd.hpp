//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DEPTH_STENCIL_BUFFER_OPTIONAL_SURFACE_REF_FWD_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_BUFFER_OPTIONAL_SURFACE_REF_FWD_HPP_INCLUDED

#include <sge/renderer/depth_stencil_buffer/surface_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace depth_stencil_buffer
{

using
optional_surface_ref
=
fcppt::optional::reference<
	sge::renderer::depth_stencil_buffer::surface
>;

}
}
}

#endif
