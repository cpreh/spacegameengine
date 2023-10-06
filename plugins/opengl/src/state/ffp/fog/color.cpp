//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/fog/color.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/fog/color.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::actor
sge::opengl::state::ffp::fog::color(sge::renderer::state::ffp::fog::color const &_color)
{
  sge::image::color::rgba32f const converted{
      sge::image::color::any::convert<sge::image::color::rgba32f_format>(_color.get())};

  return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
      [converted]
      {
        sge::opengl::call(
            ::glFogfv, sge::opengl::convert::to_gl_enum<GL_FOG_COLOR>(), converted.data());
      },
      FCPPT_TEXT("glFogfv"));
}
