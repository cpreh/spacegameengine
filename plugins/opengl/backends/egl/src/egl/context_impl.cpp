//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/context_impl.hpp>
#include <sge/opengl/egl/make_current.hpp>
#include <sge/opengl/egl/no_context.hpp>
#include <sge/opengl/egl/no_surface.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <exception>
#include <fcppt/config/external_end.hpp>

sge::opengl::egl::context_impl::context_impl(
    EGLDisplay const _display, // NOLINT(misc-misplaced-const)
    EGLConfig const _config // NOLINT(misc-misplaced-const)
    )
    : display_(_display),
      context_(::eglCreateContext(
          _display,
          _config,
          EGL_NO_CONTEXT,
          sge::opengl::egl::attribute_vector{EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE}.data()))
{
  if (context_ == sge::opengl::egl::no_context())
  {
    throw sge::renderer::exception(FCPPT_TEXT("eglCreateContext failed"));
  }
}

sge::opengl::egl::context_impl::~context_impl()
{
  if(::eglDestroyContext(display_, context_) != EGL_TRUE)
  {
    std::terminate();
  }
}

void sge::opengl::egl::context_impl::activate(
    EGLSurface const _surface // NOLINT(misc-misplaced-const)
)
{
  sge::opengl::egl::make_current(display_, _surface, context_);
}

void sge::opengl::egl::context_impl::deactivate()
{
  sge::opengl::egl::make_current(
      display_, sge::opengl::egl::no_surface(), sge::opengl::egl::no_context());
}
