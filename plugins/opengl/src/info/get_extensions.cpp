//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/opengl/parse_extensions.hpp>
#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_set.hpp>
#include <sge/opengl/info/get_extensions.hpp>

sge::opengl::info::extension_set
sge::opengl::info::get_extensions(sge::opengl::backend::current const &)
{
  return sge::opengl::parse_extensions<sge::opengl::info::extension>(
      sge::opengl::get_string(GL_EXTENSIONS));
}
