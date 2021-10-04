//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_TRANSLATE_SRGB_EMULATION_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_TRANSLATE_SRGB_EMULATION_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>


namespace sge::renderer::texture
{

SGE_RENDERER_DETAIL_SYMBOL
sge::image::color::format
translate_srgb_emulation(
	sge::renderer::texture::color_format const &
);

}

#endif
