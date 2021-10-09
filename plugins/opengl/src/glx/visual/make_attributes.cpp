//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <sge/opengl/glx/visual/make_attributes.hpp>
#include <sge/opengl/glx/visual/optional_srgb_flag.hpp>
#include <sge/opengl/glx/visual/srgb_flag.hpp>
#include <sge/opengl/visual/convert_color.hpp>
#include <sge/opengl/visual/rgb_triple.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::glx::visual::attribute_container sge::opengl::glx::visual::make_attributes(
    sge::opengl::glx::visual::optional_srgb_flag const _srgb_flag,
    sge::renderer::pixel_format::object const &_format)
{
  sge::opengl::glx::visual::attribute_container ret;

  ret.push_back(GLX_RGBA);

  ret.push_back(GLX_DOUBLEBUFFER);

  {
    sge::opengl::visual::rgb_triple const rgb(sge::opengl::visual::convert_color(_format.color()));

    ret.push_back(GLX_RED_SIZE);

    ret.push_back(rgb.red().get());

    ret.push_back(GLX_BLUE_SIZE);

    ret.push_back(rgb.blue().get());

    ret.push_back(GLX_GREEN_SIZE);

    ret.push_back(rgb.green().get());
  }

  fcppt::optional::maybe_void(
      sge::renderer::pixel_format::depth_bits(_format.depth_stencil()),
      [&ret](sge::renderer::pixel_format::bit_count const _depth_bits)
      {
        ret.push_back(GLX_DEPTH_SIZE);

        ret.push_back(fcppt::cast::to_signed(_depth_bits.get()));
      });

  fcppt::optional::maybe_void(
      sge::renderer::pixel_format::stencil_bits(_format.depth_stencil()),
      [&ret](sge::renderer::pixel_format::bit_count const _stencil_bits)
      {
        ret.push_back(GLX_STENCIL_SIZE);

        ret.push_back(fcppt::cast::to_signed(_stencil_bits.get()));
      });

  fcppt::optional::maybe_void(
      _format.multi_samples(),
      [&ret](sge::renderer::pixel_format::multi_samples const _samples)
      {
        ret.push_back(GLX_SAMPLE_BUFFERS);

        ret.push_back(GL_TRUE);

        ret.push_back(GLX_SAMPLES);

        ret.push_back(fcppt::cast::to_signed(_samples.get()));
      });

  if (_format.srgb() != sge::renderer::pixel_format::srgb::no)
  {
    fcppt::optional::maybe(
        _srgb_flag,
        [&_format]
        {
          if (_format.srgb() == sge::renderer::pixel_format::srgb::yes)
          {
            throw sge::renderer::unsupported(
                FCPPT_TEXT("sRGB visuals"),
                FCPPT_TEXT(""),
                FCPPT_TEXT("GLX_EXT_framebuffer_sRGB, GLX_ARB_framebuffer_sRGB"));
          }
        },
        [&ret](sge::opengl::glx::visual::srgb_flag const _flag)
        {
          ret.push_back(_flag.get());

          ret.push_back(GL_TRUE);
        });
  }

  ret.push_back(None);

  return ret;
}
