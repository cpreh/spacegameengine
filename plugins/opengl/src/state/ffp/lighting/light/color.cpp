//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/ffp/lighting/light/color.hpp>
#include <sge/opengl/state/ffp/lighting/light/float_ptr.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

sge::opengl::state::index_actor sge::opengl::state::ffp::lighting::light::color(
    GLenum const _name, sge::image::color::any::object const &_color)
{
  return sge::opengl::state::ffp::lighting::light::float_ptr(
      _name, sge::image::color::any::convert<sge::image::color::rgba32f_format>(_color).data());
}
