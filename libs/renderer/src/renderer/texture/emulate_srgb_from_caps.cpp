//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>


sge::renderer::texture::emulate_srgb
sge::renderer::texture::emulate_srgb_from_caps(
	sge::renderer::caps::device const &_caps
)
{
	return
		_caps.srgb_framebuffer().get()
		?
			sge::renderer::texture::emulate_srgb::no
		:
			sge::renderer::texture::emulate_srgb::yes
		;
}
