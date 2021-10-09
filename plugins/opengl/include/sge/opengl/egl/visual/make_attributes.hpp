//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_EGL_VISUAL_MAKE_ATTRIBUTES_HPP_INCLUDED
#define SGE_OPENGL_EGL_VISUAL_MAKE_ATTRIBUTES_HPP_INCLUDED

#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>

namespace sge::opengl::egl::visual
{

sge::opengl::egl::attribute_vector make_attributes(sge::renderer::pixel_format::object const &);

}

#endif
