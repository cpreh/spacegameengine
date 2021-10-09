//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/core/blend/config.hpp>

sge::opengl::state::core::blend::config::config(gl_blend_func_separate _blend_func_separate)
    : blend_func_separate_(_blend_func_separate)
{
}

sge::opengl::state::core::blend::config::gl_blend_func_separate
sge::opengl::state::core::blend::config::blend_func_separate() const
{
  return blend_func_separate_;
}
