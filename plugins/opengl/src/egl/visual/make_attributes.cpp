//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/visual/make_attributes.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/color_bits.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <EGL/eglplatform.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::egl::attribute_vector
sge::opengl::egl::visual::make_attributes(sge::renderer::pixel_format::object const &_format)
{
  sge::opengl::egl::attribute_vector result{
      EGL_BUFFER_SIZE,
      fcppt::cast::to_signed(sge::renderer::pixel_format::color_bits(_format.color()).get())};

  auto const push_attribute(
      [&result](EGLint const _attribute, EGLint const _value)
      {
        result.reserve(result.size() + 2);

        result.push_back(_attribute);

        result.push_back(_value);
      });

  fcppt::optional::maybe_void(
      sge::renderer::pixel_format::depth_bits(_format.depth_stencil()),
      [&push_attribute](sge::renderer::pixel_format::bit_count const _depth_size)
      { push_attribute(EGL_DEPTH_SIZE, fcppt::cast::to_signed(_depth_size.get())); });

  fcppt::optional::maybe_void(
      sge::renderer::pixel_format::stencil_bits(_format.depth_stencil()),
      [&push_attribute](sge::renderer::pixel_format::bit_count const _stencil_size)
      { push_attribute(EGL_STENCIL_SIZE, fcppt::cast::to_signed(_stencil_size.get())); });

  // TODO(philipp): Check extensions for srgb support

  result.push_back(EGL_NONE);

  return result;
}
