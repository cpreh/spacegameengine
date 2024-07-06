//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/get_string.hpp>
#include <sge/opengl/parse_extensions.hpp>
#include <sge/opengl/wgl/extension.hpp>
#include <sge/opengl/wgl/extension_set.hpp>
#include <sge/opengl/wgl/get_extensions.hpp>
#include <sge/opengl/wgl/scoped_current_fwd.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

sge::opengl::wgl::extension_set
sge::opengl::wgl::get_extensions(sge::opengl::wgl::scoped_current const &)
{
  // TODO: Try wglGetExtensionsStringARB?
  return sge::opengl::parse_extensions<sge::opengl::wgl::extension>(
      sge::opengl::get_string(GL_EXTENSIONS));
}
