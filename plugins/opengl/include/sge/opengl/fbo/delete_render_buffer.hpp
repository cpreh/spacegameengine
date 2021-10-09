//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_DELETE_RENDER_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_FBO_DELETE_RENDER_BUFFER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>

namespace sge::opengl::fbo
{

void delete_render_buffer(sge::opengl::fbo::config const &, GLuint);

}

#endif
