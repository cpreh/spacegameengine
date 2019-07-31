//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/convert/level.hpp>
#include <sge/renderer/texture/stage.hpp>


GLenum
sge::opengl::texture::convert::level(
	sge::renderer::texture::stage const _stage
)
{
	return
		static_cast<
			GLenum
		>(
			GL_TEXTURE0 + _stage.get()
		);
}
