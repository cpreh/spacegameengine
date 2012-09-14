/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/stencil_func.hpp>
#include <sge/opengl/state/convert/stencil_op.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/enabled_visitor.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/func_separate.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/op_separate.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/separate.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/tr1/functional.hpp>


sge::opengl::state::core::depth_stencil::stencil::enabled_visitor::enabled_visitor(
	sge::renderer::state::core::depth_stencil::stencil::ref const _ref,
	sge::renderer::state::core::depth_stencil::stencil::write_mask const _write_mask
)
:
	ref_(
		_ref
	),
	write_mask_(
		_write_mask
	)
{
}

sge::opengl::state::core::depth_stencil::stencil::enabled_visitor::result_type const
sge::opengl::state::core::depth_stencil::stencil::enabled_visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::combined const &_combined
) const
{
	return
		fcppt::assign::make_container<
			sge::opengl::state::core::depth_stencil::stencil::enabled_visitor::result_type
		>(
			sge::opengl::state::wrap_error_handler(
				std::tr1::bind(
					::glStencilFunc,
					sge::opengl::state::convert::stencil_func(
						_combined.desc().func()
					),
					static_cast<
						GLint
					>(
						ref_.get()
					),
					0u
				),
				FCPPT_TEXT("glStencilFunc")
			)
		)(
			sge::opengl::state::wrap_error_handler(
				std::tr1::bind(
					::glStencilOp,
					sge::opengl::state::convert::stencil_op(
						_combined.desc().fail_op().get()
					),
					sge::opengl::state::convert::stencil_op(
						_combined.desc().depth_fail_op().get()
					),
					sge::opengl::state::convert::stencil_op(
						_combined.desc().pass_op().get()
					)
				),
				FCPPT_TEXT("glStencilOp")
			)
		)(
			sge::opengl::state::core::depth_stencil::stencil::write_mask(
				write_mask_
			)
		);
}

sge::opengl::state::core::depth_stencil::stencil::enabled_visitor::result_type const
sge::opengl::state::core::depth_stencil::stencil::enabled_visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::separate const &_separate
) const
{
	// TODO: Check if this is supported

	return
		fcppt::assign::make_container<
			sge::opengl::state::core::depth_stencil::stencil::enabled_visitor::result_type
		>(
			sge::opengl::state::core::depth_stencil::stencil::func_separate(
				GL_FRONT,
				_separate.front().get().func(),
				ref_
			)
		)(
			sge::opengl::state::core::depth_stencil::stencil::func_separate(
				GL_BACK,
				_separate.back().get().func(),
				ref_
			)
		)(
			sge::opengl::state::core::depth_stencil::stencil::op_separate(
				GL_FRONT,
				_separate.front().get().fail_op(),
				_separate.front().get().depth_fail_op(),
				_separate.front().get().pass_op()
			)
		)(
			sge::opengl::state::core::depth_stencil::stencil::op_separate(
				GL_BACK,
				_separate.back().get().fail_op(),
				_separate.back().get().depth_fail_op(),
				_separate.back().get().pass_op()
			)
		)(
			sge::opengl::state::core::depth_stencil::stencil::write_mask(
				write_mask_
			)
		);
}
