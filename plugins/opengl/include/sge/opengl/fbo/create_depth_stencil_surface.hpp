//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_CREATE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_FBO_CREATE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>

namespace sge::opengl::fbo
{

sge::renderer::depth_stencil_buffer::surface_unique_ptr create_depth_stencil_surface(
    sge::opengl::context::object_ref,
    sge::renderer::depth_stencil_buffer::surface_parameters const &);

}

#endif
