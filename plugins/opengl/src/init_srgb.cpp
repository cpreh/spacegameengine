//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/enable.hpp>
#include <sge/opengl/init_srgb.hpp>
#include <sge/opengl/srgb_context.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>

void sge::opengl::init_srgb(
    fcppt::log::object &_log,
    sge::opengl::context::object &_context,
    sge::renderer::pixel_format::srgb const _srgb)
{
  if (_srgb == sge::renderer::pixel_format::srgb::no)
  {
    return;
  }

  sge::opengl::srgb_context const &srgb_context(
      sge::opengl::context::use<sge::opengl::srgb_context>(
          fcppt::make_ref(_context), _context.info()));

  fcppt::optional::maybe(
      srgb_context.flag(),
      [&_log, _srgb]
      {
        if (_srgb == sge::renderer::pixel_format::srgb::try_)
        {
          FCPPT_LOG_WARNING(
              _log,
              fcppt::log::out << FCPPT_TEXT("srgb::try_ was specified but srgb is not supported!"))
        }
        else
        {
          throw sge::renderer::unsupported(
              FCPPT_TEXT("srgb sampling"),
              FCPPT_TEXT("GL_VERSION_3_0"),
              FCPPT_TEXT("EXT_framebuffer_sRGB"));
        }
      },
      [](GLenum const _srgb_flag) { sge::opengl::enable(_srgb_flag); });
}
