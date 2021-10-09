//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>

sge::renderer::pixel_format::object::object(
    sge::renderer::pixel_format::color const _color,
    sge::renderer::pixel_format::depth_stencil const _depth_stencil,
    sge::renderer::pixel_format::optional_multi_samples const &_multi_samples,
    sge::renderer::pixel_format::srgb const _srgb)
    : color_(_color), depth_stencil_(_depth_stencil), multi_samples_(_multi_samples), srgb_(_srgb)
{
}

sge::renderer::pixel_format::color sge::renderer::pixel_format::object::color() const
{
  return color_;
}

sge::renderer::pixel_format::depth_stencil
sge::renderer::pixel_format::object::depth_stencil() const
{
  return depth_stencil_;
}

sge::renderer::pixel_format::optional_multi_samples
sge::renderer::pixel_format::object::multi_samples() const
{
  return multi_samples_;
}

sge::renderer::pixel_format::srgb sge::renderer::pixel_format::object::srgb() const
{
  return srgb_;
}
