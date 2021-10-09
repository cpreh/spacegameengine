//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>

GLboolean sge::opengl::convert::to_gl_bool(bool const _value)
{
  return static_cast<GLboolean>(_value ? GL_TRUE : GL_FALSE);
}
