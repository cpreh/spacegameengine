//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/glx/current.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <sge/opengl/glx/proc_address_function_ref.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <sge/opengl/glx/vsync.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/base_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::opengl::glx::current::current(
    fcppt::log::object_reference const _log,
    awl::backends::x11::window::base_ref const _window,
    sge::opengl::glx::optional_proc_address_function const &_opt_proc_address)
    : sge::opengl::backend::current(),
      log_{_log},
      window_(_window),
      proc_address_(_opt_proc_address),
      swap_functions_(fcppt::optional::map(
          _opt_proc_address,
          [](sge::opengl::glx::proc_address_function_ref const _proc_address)
          { return sge::opengl::glx::swap_functions(_proc_address.get()); }))
{
}

sge::opengl::glx::current::~current() = default;

void sge::opengl::glx::current::begin_rendering() {}

sge::opengl::backend::fun_ptr
sge::opengl::glx::current::load_function(std::string const &_name) const
{
  // TODO(philipp): Use optionals
  return fcppt::optional::maybe(
      proc_address_,
      [] { return sge::opengl::backend::fun_ptr{nullptr}; },
      [&_name](sge::opengl::glx::proc_address_function_ref const _proc_address)
      { return _proc_address.get()(fcppt::cast::to_char_ptr<GLubyte const *>(_name.c_str())); });
}

void sge::opengl::glx::current::end_rendering()
{
  if (!window_.get().destroyed())
  {
    ::glXSwapBuffers(window_.get().display().get().get(), window_.get().get());
  }
}
void sge::opengl::glx::current::vsync(sge::renderer::display_mode::vsync const _vsync)
{
  if (_vsync == sge::renderer::display_mode::vsync::on)
  {
    fcppt::optional::maybe(
        swap_functions_,
        [this]
        {
          FCPPT_LOG_ERROR(
              log_.get(),
              fcppt::log::out << FCPPT_TEXT("GLX extensions not available.")
                      FCPPT_TEXT(" Setting vsync is not supported.")

          )
        },
        [this](sge::opengl::glx::swap_functions const &_swap_functions)
        { sge::opengl::glx::vsync(log_.get(), _swap_functions, window_.get().display().get()); });
  }
}
