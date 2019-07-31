//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/fill_mode.hpp>
#include <sge/opengl/state/core/rasterizer/fill_mode.hpp>
#include <fcppt/text.hpp>


sge::opengl::state::actor
sge::opengl::state::core::rasterizer::fill_mode(
	sge::renderer::state::core::rasterizer::fill_mode const _mode
)
{
	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::actor
		>(
			[
				_mode
			]{
				return
					sge::opengl::call(
						::glPolygonMode,
						sge::opengl::convert::to_gl_enum<
							GL_FRONT_AND_BACK
						>(),
						sge::opengl::state::convert::fill_mode(
							_mode
						)
					);
			},
			FCPPT_TEXT("glPolygonMode")
		);
}
