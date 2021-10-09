//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_FBO_CONST_RENDER_BUFFER_REF_HPP_INCLUDED
#define SGE_OPENGL_FBO_CONST_RENDER_BUFFER_REF_HPP_INCLUDED

#include <sge/opengl/fbo/render_buffer_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::opengl::fbo
{

using const_render_buffer_ref = fcppt::reference<sge::opengl::fbo::render_buffer const>;

}

#endif
