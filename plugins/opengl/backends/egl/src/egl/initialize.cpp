//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/egl/initialize.hpp>
#include <sge/opengl/egl/major_version.hpp>
#include <sge/opengl/egl/minor_version.hpp>
#include <sge/opengl/egl/version.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <EGL/eglplatform.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::egl::version
sge::opengl::egl::initialize(EGLDisplay const _display // NOLINT(misc-misplaced-const)
)
{
  EGLint major{};

  EGLint minor{};

  if (::eglInitialize(_display, &major, &minor) != EGL_TRUE)
  {
    throw sge::renderer::exception(FCPPT_TEXT("Failed to initialize EGL"));
  }

  return sge::opengl::egl::version(
      sge::opengl::egl::major_version(major), sge::opengl::egl::minor_version(minor));
}
