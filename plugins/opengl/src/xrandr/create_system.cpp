//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/create_system.hpp>
#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/get_extension.hpp>
#include <sge/opengl/xrandr/get_version.hpp>
#include <sge/opengl/xrandr/optional_system_unique_ptr.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/opengl/xrandr/version.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>

sge::opengl::xrandr::optional_system_unique_ptr sge::opengl::xrandr::create_system(
    fcppt::log::object_reference const _log, awl::backends::x11::display_ref const _display)
{
  return fcppt::optional::maybe(
      sge::opengl::xrandr::get_extension(_display),
      [&_log]
      {
        FCPPT_LOG_WARNING(_log.get(), fcppt::log::out << FCPPT_TEXT("xrandr extension not found"))

        return sge::opengl::xrandr::optional_system_unique_ptr();
      },
      [&_log, &_display](sge::opengl::xrandr::extension const _extension)
      {
        sge::opengl::xrandr::version const version{
            sge::opengl::xrandr::get_version(_extension, _display)};

        if (version < sge::opengl::xrandr::version{
                          sge::opengl::xrandr::version::major_type{1},
                          sge::opengl::xrandr::version::minor_type{3}})
        {
          FCPPT_LOG_WARNING(
              _log.get(),
              fcppt::log::out << FCPPT_TEXT("xrandr version ") << version << FCPPT_TEXT(" too old"))

          return sge::opengl::xrandr::optional_system_unique_ptr();
        }

        return sge::opengl::xrandr::optional_system_unique_ptr(
            fcppt::make_unique_ptr<sge::opengl::xrandr::system>(_extension));
      });
}
