//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_EMULATE_SRGB_FROM_CAPS_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_EMULATE_SRGB_FROM_CAPS_HPP_INCLUDED

#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>


namespace sge::renderer::texture
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::texture::emulate_srgb
emulate_srgb_from_caps(
	sge::renderer::caps::device const &
);

}

#endif
