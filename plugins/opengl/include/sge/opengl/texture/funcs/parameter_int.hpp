//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_FUNCS_PARAMETER_INT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_PARAMETER_INT_HPP_INCLUDED

#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

namespace sge::opengl::texture::funcs
{

void parameter_int(sge::opengl::texture::binding const &, GLenum name, GLint value);

}

#endif
