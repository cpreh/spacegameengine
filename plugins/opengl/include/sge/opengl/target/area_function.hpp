//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TARGET_AREA_FUNCTION_HPP_INCLUDED
#define SGE_OPENGL_TARGET_AREA_FUNCTION_HPP_INCLUDED

#include <sge/opengl/apientry.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

namespace sge::opengl::target
{

using area_function = void(SGE_OPENGL_APIENTRY &)(GLint, GLint, GLsizei, GLsizei);

}

#endif
