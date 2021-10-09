//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/windows/visual/make_format.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/color_bits.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_bit_count.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/const.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/from.hpp>

PIXELFORMATDESCRIPTOR const sge::opengl::windows::visual::make_format(
    sge::renderer::pixel_format::color const _color,
    sge::renderer::pixel_format::depth_stencil const _depth_stencil)
{
  auto const convert_optional_bit_count(
      [](sge::renderer::pixel_format::optional_bit_count const _bit_count) -> BYTE
      {
        return fcppt::cast::size<BYTE>(
            fcppt::optional::from(
                _bit_count, fcppt::const_(sge::renderer::pixel_format::bit_count{0u}))
                .get());
      });

  PIXELFORMATDESCRIPTOR const ret = {
      sizeof(PIXELFORMATDESCRIPTOR),
      1, // Version Number
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      fcppt::cast::size<BYTE>(sge::renderer::pixel_format::color_bits(_color).get()),
      0,
      0,
      0,
      0,
      0,
      0, // Color Bits Ignored
      0, // No Alpha Buffer
      0, // Shift Bit Ignored
      0, // No Accumulation Buffer
      0,
      0,
      0,
      0, // Accumulation Bits Ignored
      convert_optional_bit_count(sge::renderer::pixel_format::depth_bits(_depth_stencil)),
      convert_optional_bit_count(sge::renderer::pixel_format::stencil_bits(_depth_stencil)),
      0, // No Auxiliary Buffer
      PFD_MAIN_PLANE, // Main Drawing Layer
      0, // Reserved
      0,
      0,
      0 // Layer Masks Ignored
  };

  return ret;
}
