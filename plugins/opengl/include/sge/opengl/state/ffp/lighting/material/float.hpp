//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_LIGHTING_MATERIAL_FLOAT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_LIGHTING_MATERIAL_FLOAT_HPP_INCLUDED

#include <sge/opengl/state/actor.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

namespace sge::opengl::state::ffp::lighting::material
{

sge::opengl::state::actor float_(GLenum face, GLenum what, GLfloat value);

}

#endif
