//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/stencil_func.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/func_separate.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::state::actor
sge::opengl::state::core::depth_stencil::stencil::func_separate(
	sge::opengl::state::core::depth_stencil::stencil::config const &_config,
	GLenum const _side,
	sge::renderer::state::core::depth_stencil::stencil::func const _func,
	sge::renderer::state::core::depth_stencil::stencil::ref const _ref,
	sge::renderer::state::core::depth_stencil::stencil::read_mask const _read_mask
)
{
	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::actor
		>(
			[
				&_config,
				_side,
				_func,
				_ref,
				_read_mask
			]{
				return
					sge::opengl::call_fun_ref(
						_config.stencil_func_separate(),
						_side,
						sge::opengl::state::convert::stencil_func(
							_func
						),
						fcppt::cast::to_signed(
							_ref.get()
						),
						_read_mask.get()
					);
			},
			FCPPT_TEXT("glStencilFuncSeparate")
		);
}
