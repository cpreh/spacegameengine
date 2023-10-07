//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/ext.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/dest_blend_func.hpp>
#include <sge/opengl/state/convert/source_blend_func.hpp>
#include <sge/opengl/state/core/blend/alpha_enabled.hpp>
#include <sge/opengl/state/core/blend/context.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/match.hpp>

sge::opengl::state::actor sge::opengl::state::core::blend::alpha_enabled(
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::core::blend::alpha_enabled const &_variant)
{
  return fcppt::variant::match(
      _variant,
      [](sge::renderer::state::core::blend::combined const &_combined)
      {
        return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
            [_combined]
            {
              return sge::opengl::call(
                  ::glBlendFunc,
                  sge::opengl::state::convert::source_blend_func(_combined.source()),
                  sge::opengl::state::convert::dest_blend_func(_combined.dest()));
            },
            FCPPT_TEXT("glBlendFunc"));
      },
      [_context](sge::renderer::state::core::blend::separate const &_separate)
      {
        sge::opengl::fun_ref<PFNGLBLENDFUNCSEPARATEPROC> const func{
            fcppt::optional::to_exception(
                sge::opengl::context::use<sge::opengl::state::core::blend::context>(
                    _context, _context.get().info())
                    .config(),
                []
                {
                  return sge::renderer::unsupported{
                      FCPPT_TEXT("blend func separate"), FCPPT_TEXT("1.4"), FCPPT_TEXT("")};
                })
                .blend_func_separate()};

        return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
            [_separate, func]
            {
              return sge::opengl::call_fun_ref(
                  func,
                  sge::opengl::state::convert::source_blend_func(_separate.color_source().get()),
                  sge::opengl::state::convert::dest_blend_func(_separate.color_dest().get()),
                  sge::opengl::state::convert::source_blend_func(_separate.alpha_source().get()),
                  sge::opengl::state::convert::dest_blend_func(_separate.alpha_dest().get()));
            },
            FCPPT_TEXT("glBlendFuncSeparate"));
      });
}
