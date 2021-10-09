//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/material/color.hpp>
#include <fcppt/text.hpp>

sge::opengl::state::actor sge::opengl::state::ffp::lighting::material::color(
    GLenum const _face, GLenum const _what, sge::image::color::any::object const &_color)
{
  sge::image::color::rgba32f const converted{
      sge::image::color::any::convert<sge::image::color::rgba32f_format>(_color)};

  return sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
      [_face, _what, converted]
      { sge::opengl::call(::glMaterialfv, _face, _what, converted.data()); },
      FCPPT_TEXT("glMaterialfv"));
}
