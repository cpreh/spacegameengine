//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/convert/level.hpp>
#include <sge/opengl/texture/funcs/set_client_level.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe.hpp>

void sge::opengl::texture::funcs::set_client_level(
    fcppt::log::object &_log,
    sge::opengl::context::object &_context,
    sge::renderer::texture::stage const _stage)
{
  // TODO(philipp): Should we require multi_config as an argument here?

  fcppt::optional::maybe(
      sge::opengl::context::use<sge::opengl::texture::multi_context>(
          fcppt::make_ref(_context), _context.info())
          .config(),
      [&_log, _stage]
      {
        if (_stage.get() == 0U)
        {
          return;
        }

        FCPPT_LOG_ERROR(
            _log,
            fcppt::log::out << FCPPT_TEXT("Tried to set texture coordinates for stage ") << _stage
                            << FCPPT_TEXT(" but opengl does not support it."))
      },
      [_stage](sge::opengl::texture::multi_config const &_config)
      {
        sge::opengl::call_fun_ref(
            _config.client_active_texture(), sge::opengl::texture::convert::level(_stage));

        SGE_OPENGL_CHECK_STATE(
            (fcppt::format(FCPPT_TEXT("glClientActiveTexture failed for stage %1%")) % _stage)
                .str(),
            sge::renderer::exception)
      });
}
