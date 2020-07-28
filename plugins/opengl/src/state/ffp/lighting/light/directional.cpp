//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/light/directional.hpp>
#include <sge/opengl/state/ffp/lighting/light/position_impl.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional.hpp>
#include <fcppt/math/vector/push_back.hpp>


sge::opengl::state::index_actor_vector
sge::opengl::state::ffp::lighting::light::directional(
	sge::renderer::state::ffp::lighting::light::directional const &_directional
)
{
	return
		sge::opengl::state::index_actor_vector{
			sge::opengl::state::ffp::lighting::light::position_impl(
				fcppt::math::vector::push_back(
					_directional.direction().get(),
					// special value to make this a directional light
					0.F
				)
			)
		};
}
