//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/cg/texture/disable.hpp>
#include <sge/opengl/cg/texture/loaded_object.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>


void
sge::opengl::cg::texture::disable(
	sge::renderer::cg::loaded_texture const &_texture
)
{
	dynamic_cast<
		sge::opengl::cg::texture::loaded_object const &
	>(
		_texture
	).disable();
}
