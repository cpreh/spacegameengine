//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/glx/current.hpp>
#include <sge/opengl/glx/make_current.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/visual/object.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/backends/x11/window/base_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::glx::context::context(
    fcppt::log::object_reference const _log,
    awl::backends::x11::window::base_ref const _window,
    sge::opengl::glx::optional_proc_address_function const _proc_address)
    : sge::opengl::backend::context(),
      log_{_log},
      window_(_window),
      proc_address_(_proc_address),
      context_(::glXCreateContext(
          window_.get().display().get().get(),
          // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
          const_cast<XVisualInfo *>(window_.get().x11_visual().info()),
          nullptr,
          True))
{
  if (context_ == nullptr)
  {
    throw sge::renderer::exception(FCPPT_TEXT("glXCreateContext() failed!"));
  }
}

sge::opengl::glx::context::~context()
{
  ::glXDestroyContext(window_.get().display().get().get(), context_);
}

sge::opengl::backend::current_unique_ptr sge::opengl::glx::context::activate()
{
  sge::opengl::glx::make_current(
      window_.get().display().get().get(), window_.get().get(), context_);

  return fcppt::unique_ptr_to_base<sge::opengl::backend::current>(
      fcppt::make_unique_ptr<sge::opengl::glx::current>(log_, window_, proc_address_));
}

void sge::opengl::glx::context::deactivate(sge::opengl::backend::current_unique_ptr &&)
{
  sge::opengl::glx::make_current(window_.get().display().get().get(), None, nullptr);
}
