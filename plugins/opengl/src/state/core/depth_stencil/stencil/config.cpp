//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/state/core/depth_stencil/stencil/config.hpp>


sge::opengl::state::core::depth_stencil::stencil::config::config(
	gl_stencil_func_separate _stencil_func_separate,
	gl_stencil_op_separate _stencil_op_separate
)
:
	stencil_func_separate_(
		_stencil_func_separate
	),
	stencil_op_separate_(
		_stencil_op_separate
	)
{
}

sge::opengl::state::core::depth_stencil::stencil::config::gl_stencil_func_separate
sge::opengl::state::core::depth_stencil::stencil::config::stencil_func_separate() const
{
	return
		stencil_func_separate_;
}

sge::opengl::state::core::depth_stencil::stencil::config::gl_stencil_op_separate
sge::opengl::state::core::depth_stencil::stencil::config::stencil_op_separate() const
{
	return
		stencil_op_separate_;
}
