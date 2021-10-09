//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/const_context_ref.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/get_config.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>

sge::opengl::fbo::config const &
sge::opengl::fbo::get_config(sge::opengl::fbo::const_context_ref const _context)
{
  return fcppt::optional::to_exception(
      _context.get().config(),
      []
      {
        return sge::renderer::unsupported(
            FCPPT_TEXT("glGenFrameBuffers"),
            FCPPT_TEXT("Opengl-3.0"),
            FCPPT_TEXT("frame_buffer_ext"));
      });
}
