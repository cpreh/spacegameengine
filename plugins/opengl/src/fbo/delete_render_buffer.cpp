//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/delete_render_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::fbo::delete_render_buffer(
	sge::opengl::fbo::config const &_config,
	GLuint const _id
)
{
	sge::opengl::call_fun_ref(
		_config.delete_renderbuffers(),
		1,
		&_id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Deleting a render buffer failed."),
		sge::renderer::exception
	)
}
