//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/funcs/gen.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::opengl::texture::id
sge::opengl::texture::funcs::gen()
{
	GLuint ret{};

	sge::opengl::call(
		::glGenTextures,
		1,
		&ret
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenTextures failed"),
		sge::renderer::exception
	)

	return
		sge::opengl::texture::id(
			ret
		);
}
