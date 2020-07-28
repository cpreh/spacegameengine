//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/create_id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::opengl::fbo::id
sge::opengl::fbo::create_id(
	sge::opengl::fbo::config const &_context
)
{
	GLuint id{};

	sge::opengl::call_fun_ref(
		_context.gen_framebuffers(),
		1,
		&id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenFramebuffers failed"),
		sge::renderer::exception
	)

	return
		sge::opengl::fbo::id(
			id
		);
}
