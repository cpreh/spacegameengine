//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/config.hpp>
#include <sge/opengl/backend/create_system.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/backend/system_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/system/object_ref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/config/platform.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/first_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/either/try_call.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>
#ifdef SGE_OPENGL_HAVE_SDL
#include <sge/opengl/sdl/backend_system.hpp>
#include <awl/backends/sdl/system/object.hpp>
#endif
#ifdef SGE_OPENGL_HAVE_EGL
#include <sge/opengl/egl/system.hpp>
#endif
#ifdef SGE_OPENGL_HAVE_GLX
#include <sge/opengl/glx/system.hpp>
#include <awl/backends/x11/system/object.hpp>
#endif
#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
#include <sge/opengl/wgl/system.hpp>
#endif

namespace
{

using create_function_exn = fcppt::function<sge::opengl::backend::system_unique_ptr(
    fcppt::log::object_reference, awl::system::object_ref)>;

using create_function_exn_vector = std::vector<create_function_exn>;

create_function_exn_vector create_functions_exn()
{
  return create_function_exn_vector
  {
#ifdef SGE_OPENGL_HAVE_SDL
    create_function_exn{
        [](fcppt::log::object_reference, awl::system::object_ref const _awl_system)
        {
          return fcppt::unique_ptr_to_base<sge::opengl::backend::system>(
              fcppt::make_unique_ptr<sge::opengl::sdl::backend_system>(
                  fcppt::optional::to_exception(
                      fcppt::cast::dynamic<awl::backends::sdl::system::object>(_awl_system.get()),
                      [] {
                        return sge::renderer::exception{
                            FCPPT_TEXT("awl::system is not an SDL system.")};
                      })));
        }},
#endif
#ifdef SGE_OPENGL_HAVE_EGL
        create_function_exn{
            [](fcppt::log::object_reference const _log, awl::system::object_ref const _awl_system)
            {
              return fcppt::unique_ptr_to_base<sge::opengl::backend::system>(
                  fcppt::make_unique_ptr<sge::opengl::egl::system>(_log, _awl_system));
            }},
#endif
#ifdef SGE_OPENGL_HAVE_GLX
        create_function_exn{
            [](fcppt::log::object_reference const _log, awl::system::object_ref const _awl_system)
            {
              return fcppt::unique_ptr_to_base<sge::opengl::backend::system>(
                  fcppt::make_unique_ptr<sge::opengl::glx::system>(
                      _log,
                      fcppt::optional::to_exception(
                          fcppt::cast::dynamic<awl::backends::x11::system::object>(
                              _awl_system.get()),
                          [] {
                            return sge::renderer::exception{
                                FCPPT_TEXT("Backend system is not an X11 system.")};
                          })));
            }},
#endif
#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
        create_function_exn{
            [](fcppt::log::object_reference, awl::system::object_ref const _awl_system)
            {
              return fcppt::unique_ptr_to_base<sge::opengl::backend::system>(
                  fcppt::make_unique_ptr<sge::opengl::wgl::system>(_awl_system.get()));
            }},
#endif
        create_function_exn
    {
      [] [[noreturn]] (fcppt::log::object_reference,
         awl::system::object_ref) -> sge::opengl::backend::system_unique_ptr
      { throw sge::renderer::exception{fcppt::string{FCPPT_TEXT("All possibilities exhausted.")}}; }
    }
  };
}

using create_function = fcppt::function<
    fcppt::either::object<fcppt::string, sge::opengl::backend::system_unique_ptr>()>;

using create_function_vector = std::vector<create_function>;

create_function_vector
create_functions(fcppt::log::object_reference const _log, awl::system::object_ref const _awl_system)
{
  return fcppt::algorithm::map<create_function_vector>(
      create_functions_exn(),
      [&_log, &_awl_system](create_function_exn &&_function)
      {
        return create_function{
            [_log, _awl_system, function = std::move(_function)]()
                -> fcppt::either::object<fcppt::string, sge::opengl::backend::system_unique_ptr>
            {
              return fcppt::either::try_call<fcppt::exception>(
                  [&function, &_log, &_awl_system]() { return function(_log, _awl_system); },
                  [](fcppt::exception const &_error) -> fcppt::string { return _error.string(); });
            }};
      });
}

}

sge::opengl::backend::system_unique_ptr sge::opengl::backend::create_system(
    fcppt::log::object_reference const _log, awl::system::object_ref const _awl_system)
{
  return fcppt::either::to_exception(
      fcppt::either::first_success(create_functions(_log, _awl_system)),
      [](std::vector<fcppt::string> const &_failures)
      {
        return sge::renderer::exception{
            FCPPT_TEXT("Cannot create an OpenGL backend: ") +
            fcppt::algorithm::join_strings(_failures, fcppt::string{FCPPT_TEXT(", ")})};
      });
}
