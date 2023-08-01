//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/egl/bind_api.hpp>
#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/create_display.hpp>
#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/system.hpp>
#include <sge/opengl/egl/version_output.hpp>
#include <sge/opengl/egl/visual/to_config.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/system/object_ref.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>

sge::opengl::egl::system::system(
    fcppt::log::object_reference const _log, awl::system::object_ref const _awl_system)
    : sge::opengl::backend::system(),
      log_{_log},
      awl_system_(_awl_system),
      egl_display_(sge::opengl::egl::create_display(_log, _awl_system)),
      init_(egl_display_->get())
{
  FCPPT_LOG_INFO(_log.get(), fcppt::log::out << FCPPT_TEXT("EGL version is ") << init_.version())

  sge::opengl::egl::bind_api(EGL_OPENGL_API);
}

sge::opengl::egl::system::~system() = default;

awl::visual::object_unique_ptr
sge::opengl::egl::system::create_visual(sge::renderer::pixel_format::object const &_pixel_format)
{
  return egl_display_->create_visual(init_, _pixel_format);
}

sge::opengl::backend::context_unique_ptr
sge::opengl::egl::system::create_context(sge::window::object_ref const _window)
{
  // NOLINTNEXTLINE(misc-misplaced-const)
  EGLConfig const config{sge::opengl::egl::visual::to_config(
      log_.get(), egl_display_->get(), _window.get().awl_object().visual())};

  return fcppt::unique_ptr_to_base<sge::opengl::backend::context>(
      fcppt::make_unique_ptr<sge::opengl::egl::context>(
          egl_display_->get(), config, egl_display_->create_surface(config, _window)));
}
