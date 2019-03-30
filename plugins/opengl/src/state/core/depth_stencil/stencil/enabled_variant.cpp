/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/stencil_func.hpp>
#include <sge/opengl/state/convert/stencil_op.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config_fwd.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/context.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/enabled_variant.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/func_separate.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/op_separate.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/separate.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::depth_stencil::stencil::enabled_variant(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::depth_stencil::stencil::ref const _ref,
	sge::renderer::state::core::depth_stencil::stencil::read_mask const _read_mask,
	sge::renderer::state::core::depth_stencil::stencil::write_mask const _write_mask,
	sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &_variant
)
{
	return
		fcppt::variant::match(
			_variant,
			[
				_ref,
				_read_mask,
				_write_mask
			](
				sge::renderer::state::core::depth_stencil::stencil::combined const &_combined
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::wrap_error_handler<
							sge::opengl::state::actor
						>(
							[
								_ref,
								_read_mask,
								func = _combined.desc().func()
							]{
								return
									sge::opengl::call(
										::glStencilFunc,
										sge::opengl::state::convert::stencil_func(
											func
										),
										fcppt::cast::to_signed(
											_ref.get()
										),
										_read_mask.get()
									);
							},
							FCPPT_TEXT("glStencilFunc")
						),
						sge::opengl::state::wrap_error_handler<
							sge::opengl::state::actor
						>(
							[
								fail_op = _combined.desc().fail_op(),
								depth_fail_op = _combined.desc().depth_fail_op(),
								pass_op = _combined.desc().pass_op()
							]{
								return
									sge::opengl::call(
										::glStencilOp,
										sge::opengl::state::convert::stencil_op(
											fail_op.get()
										),
										sge::opengl::state::convert::stencil_op(
											depth_fail_op.get()
										),
										sge::opengl::state::convert::stencil_op(
											pass_op.get()
										)
									);
							},
							FCPPT_TEXT("glStencilOp")
						),
						sge::opengl::state::core::depth_stencil::stencil::write_mask(
							_write_mask
						)
					};
			},
			[
				&_context,
				_ref,
				_read_mask,
				_write_mask
			](
				sge::renderer::state::core::depth_stencil::stencil::separate const &_separate
			)
			{
				sge::opengl::state::core::depth_stencil::stencil::config const &config(
					fcppt::optional::to_exception(
						sge::opengl::context::use<
							sge::opengl::state::core::depth_stencil::stencil::context
						>(
							_context,
							_context.info()
						).config(),
						[]{
							return
								sge::renderer::unsupported{
									FCPPT_TEXT("stencil func separate"),
									FCPPT_TEXT("2.0"),
									FCPPT_TEXT("")
								};
						}
					)
				);

				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::core::depth_stencil::stencil::func_separate(
							config,
							GL_FRONT,
							_separate.front().get().func(),
							_ref,
							_read_mask
						),
						sge::opengl::state::core::depth_stencil::stencil::func_separate(
							config,
							GL_BACK,
							_separate.back().get().func(),
							_ref,
							_read_mask
						),
						sge::opengl::state::core::depth_stencil::stencil::op_separate(
							config,
							GL_FRONT,
							_separate.front().get().fail_op(),
							_separate.front().get().depth_fail_op(),
							_separate.front().get().pass_op()
						),
						sge::opengl::state::core::depth_stencil::stencil::op_separate(
							config,
							GL_BACK,
							_separate.back().get().fail_op(),
							_separate.back().get().depth_fail_op(),
							_separate.back().get().pass_op()
						),
						sge::opengl::state::core::depth_stencil::stencil::write_mask(
							_write_mask
						)
					};
			}
		);
}
