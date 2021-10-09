//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_VF_VERTEX_ATTRIB_POINTER_HPP_INCLUDED
#define SGE_OPENGL_VF_VERTEX_ATTRIB_POINTER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/attribute_config_fwd.hpp>

namespace sge::opengl::vf
{

void vertex_attrib_pointer(
    sge::opengl::vf::attribute_config const &,
    GLuint index,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    void const *pointer);

}

#endif
