//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/convert/projection.hpp>
#include <sge/opengl/state/convert/matrix_mode.hpp>
#include <sge/opengl/state/ffp/transform/matrix_mode.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix_and_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>


void
sge::opengl::state::ffp::transform::set_matrix_and_mode(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::transform::mode const _mode,
	sge::renderer::matrix4 const &_matrix
)
{
	sge::opengl::state::ffp::transform::matrix_mode(
		sge::opengl::state::convert::matrix_mode(
			_mode
		)
	);

	sge::opengl::state::ffp::transform::set_matrix(
		_context,
		_mode
		==
		sge::renderer::state::ffp::transform::mode::projection
		?
			sge::opengl::convert::projection(
				_matrix
			)
		:
			_matrix
	);
}
