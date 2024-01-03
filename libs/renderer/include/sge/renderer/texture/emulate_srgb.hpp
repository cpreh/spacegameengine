//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_EMULATE_SRGB_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_EMULATE_SRGB_HPP_INCLUDED

#include <sge/renderer/texture/emulate_srgb_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::texture
{

enum class emulate_srgb
{
  /**
	\brief srgb color formats will be created as srgb textures

	This option should be used when hardware gamma correction is available.
	*/
  no,
  /**
	\brief srgb color formats will be created as normal rgb textures

	When a texture is mapped, the color format will still be srgb, so the
	texture can easily be mapped and filled by an srgb image, for example.
	However, gamma correction will not work at all. This compatibility
	option should be used when hardware gamma correction is not available.
	*/
  yes
};

}

#endif
