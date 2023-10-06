//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/clear/back_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/clear/back_buffer_value.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <fcppt/text.hpp>

void sge::opengl::clear::back_buffer(sge::renderer::clear::back_buffer_value const &_value)
{
  sge::image::color::rgba32f const fcolor(
      sge::image::color::any::convert<sge::image::color::rgba32f_format>(_value));

  sge::opengl::call(
      ::glClearColor,
      fcolor.get(mizuiro::color::channel::red()),
      fcolor.get(mizuiro::color::channel::green()),
      fcolor.get(mizuiro::color::channel::blue()),
      fcolor.get(mizuiro::color::channel::alpha()));

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glClearColor failed"), sge::renderer::exception)
}
