//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_GLX_VISUAL_CREATE_HPP_INCLUDED
#define SGE_OPENGL_GLX_VISUAL_CREATE_HPP_INCLUDED

#include <sge/opengl/glx/visual/optional_srgb_flag_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/system/object_ref.hpp>
#include <awl/visual/object_unique_ptr.hpp>

namespace sge::opengl::glx::visual
{

awl::visual::object_unique_ptr create(
    sge::opengl::glx::visual::optional_srgb_flag,
    awl::backends::x11::system::object_ref,
    sge::renderer::pixel_format::object const &);

}

#endif
