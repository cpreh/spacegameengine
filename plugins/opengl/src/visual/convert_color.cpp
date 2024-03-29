//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/visual/convert_color.hpp>
#include <sge/opengl/visual/rgb_triple.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::visual::rgb_triple
sge::opengl::visual::convert_color(sge::renderer::pixel_format::color const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case sge::renderer::pixel_format::color::depth16:
    return sge::opengl::visual::rgb_triple(
        sge::opengl::visual::rgb_triple::red_bits(
            5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            ),
        sge::opengl::visual::rgb_triple::green_bits(
            // TODO(philipp): is this ok?
            6 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            ),
        sge::opengl::visual::rgb_triple::blue_bits(
            5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            ));
  case sge::renderer::pixel_format::color::depth32:
    return sge::opengl::visual::rgb_triple(
        sge::opengl::visual::rgb_triple::red_bits(
            8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            ),
        sge::opengl::visual::rgb_triple::green_bits(
            8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            ),
        sge::opengl::visual::rgb_triple::blue_bits(
            8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            ));
  }

  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
