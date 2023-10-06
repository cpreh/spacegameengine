//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/element_count.hpp>
#include <sge/opengl/vf/convert_color_format.hpp>
#include <sge/opengl/vf/extra_elements.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/extra_any.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/variant/match.hpp>

GLint sge::opengl::vf::extra_elements(sge::renderer::vf::dynamic::extra_any const &_any)
{
  return fcppt::variant::match(
      _any,
      [](sge::renderer::vf::dynamic::vector const &_vector)
      { return fcppt::cast::size<GLint>(fcppt::cast::to_signed(_vector.element_count().get())); },
      [](sge::renderer::vf::dynamic::color const &_color)
      {
        return fcppt::cast::size<GLint>(fcppt::cast::to_signed(sge::image::color::element_count(
            sge::opengl::vf::convert_color_format(_color.color_format()))));
      });
}
