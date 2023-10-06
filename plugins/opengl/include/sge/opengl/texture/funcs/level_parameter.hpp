//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_FUNCS_LEVEL_PARAMETER_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_LEVEL_PARAMETER_HPP_INCLUDED

#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>

namespace sge::opengl::texture::funcs
{

GLint level_parameter(
    sge::opengl::texture::binding const &,
    sge::opengl::texture::buffer_type,
    sge::renderer::texture::mipmap::level,
    GLenum what);

}

#endif
