//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/core/rasterizer/cull_mode.hpp>
#include <sge/opengl/state/core/rasterizer/fill_mode.hpp>
#include <sge/opengl/state/core/rasterizer/make_actors.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::rasterizer::make_actors(
	sge::renderer::state::core::rasterizer::parameters const &_parameters
)
{
	return
		fcppt::container::join(
			sge::opengl::state::core::rasterizer::cull_mode(
				_parameters.cull_mode()
			),
			sge::opengl::state::actor_vector{
				sge::opengl::state::core::rasterizer::fill_mode(
					_parameters.fill_mode()
				),
				sge::opengl::state::actor{
					std::bind(
						sge::opengl::enable_bool,
						GL_SCISSOR_TEST,
						_parameters.enable_scissor_test().get()
					)
				}
			}
		);
}
