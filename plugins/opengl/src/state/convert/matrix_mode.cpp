//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/matrix_mode.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::matrix_mode(
	sge::renderer::state::ffp::transform::mode const _mode
)
{
	switch(
		_mode
	)
	{
	case sge::renderer::state::ffp::transform::mode::world:
		return GL_MODELVIEW;
	case sge::renderer::state::ffp::transform::mode::projection:
		return GL_PROJECTION;
	case sge::renderer::state::ffp::transform::mode::texture:
		return GL_TEXTURE;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
