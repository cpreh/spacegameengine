//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/get_ints.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::get_ints(
	GLenum const _what,
	GLint *const _ret
)
{
	sge::opengl::call(
		::glGetIntegerv,
		_what,
		_ret
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetIntegerv failed"),
		sge::renderer::exception
	)
}
