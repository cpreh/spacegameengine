//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>

sge::renderer::texture::color_format::color_format(
    sge::image::color::format const _format,
    sge::renderer::texture::emulate_srgb const _emulate_srgb)
    : format_(_format), emulate_srgb_(_emulate_srgb)
{
}

sge::image::color::format sge::renderer::texture::color_format::format() const { return format_; }

sge::renderer::texture::emulate_srgb sge::renderer::texture::color_format::emulate_srgb() const
{
  return emulate_srgb_;
}
