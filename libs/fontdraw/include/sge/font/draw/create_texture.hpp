//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_DRAW_CREATE_TEXTURE_HPP_INCLUDED
#define SGE_FONT_DRAW_CREATE_TEXTURE_HPP_INCLUDED

#include <sge/font/text_fwd.hpp>
#include <sge/font/draw/detail/symbol.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/texture/part_unique_ptr.hpp>

namespace sge::font::draw
{

SGE_FONT_DRAW_DETAIL_SYMBOL
sge::texture::part_unique_ptr create_texture(
    sge::renderer::device::core_ref,
    sge::font::text &, // NOLINT(google-runtime-references)
    sge::image::color::format,
    sge::renderer::texture::emulate_srgb);

}

#endif
