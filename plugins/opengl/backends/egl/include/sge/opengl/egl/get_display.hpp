//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_EGL_GET_DISPLAY_HPP_INCLUDED
#define SGE_OPENGL_EGL_GET_DISPLAY_HPP_INCLUDED

#include <sge/opengl/egl/no_display.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::egl
{

template <typename NativeDisplay>
EGLDisplay
get_display(NativeDisplay const _native // NOLINT(readability-avoid-const-params-in-decls)
)
{
  // NOLINTNEXTLINE(misc-misplaced-const)
  EGLDisplay const result(::eglGetDisplay(_native));

  if (result == sge::opengl::egl::no_display())
  {
    throw sge::renderer::exception(FCPPT_TEXT("eglGetDisplay failed"));
  }

  return result;
}

}

#endif
