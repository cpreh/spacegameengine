//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

void sge::opengl::enable_bool(GLenum const _what, bool const _enable)
{
  if (_enable)
  {
    sge::opengl::enable(_what);
  }
  else
  {
    sge::opengl::disable(_what);
  }
}
