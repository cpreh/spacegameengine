/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/stencil_op.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/op_separate.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/depth_fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/pass_op.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor
sge::opengl::state::core::depth_stencil::stencil::op_separate(
	GLenum const _side,
	sge::renderer::state::core::depth_stencil::stencil::fail_op const _fail_op,
	sge::renderer::state::core::depth_stencil::stencil::depth_fail_op const _depth_fail_op,
	sge::renderer::state::core::depth_stencil::stencil::pass_op const _pass_op
)
{
	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::actor
		>(
			std::bind(
				::glStencilOpSeparate,
				_side,
				sge::opengl::state::convert::stencil_op(
					_fail_op.get()
				),
				sge::opengl::state::convert::stencil_op(
					_depth_fail_op.get()
				),
				sge::opengl::state::convert::stencil_op(
					_pass_op.get()
				)
			),
			FCPPT_TEXT("glStencilOpSeparate")
		);
}
