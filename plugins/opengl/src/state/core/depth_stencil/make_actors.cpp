//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/core/depth_stencil/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/depth/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/make_actors.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <fcppt/container/join.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::depth_stencil::make_actors(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::depth_stencil::parameters const &_parameters
)
{
	return
		fcppt::container::join(
			sge::opengl::state::core::depth_stencil::depth::make_actors(
				_parameters.depth_variant()
			),
			sge::opengl::state::core::depth_stencil::stencil::make_actors(
				_context,
				_parameters.stencil_variant()
			)
		);
}
