//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/attribute_config.hpp>
#include <sge/opengl/vf/vertex_attrib_pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::vf::vertex_attrib_pointer(
	sge::opengl::vf::attribute_config const &_config,
	GLuint const _index,
	GLint const _size,
	GLenum const _type,
	GLboolean const _normalized,
	GLsizei const _stride,
	void const *const _pointer
)
{
	sge::opengl::call_fun_ref(
		_config.vertex_attrib_pointer(),
		_index,
		_size,
		_type,
		_normalized,
		_stride,
		_pointer
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Setting a vertex attribute pointer failed"),
		sge::renderer::exception
	)
}
