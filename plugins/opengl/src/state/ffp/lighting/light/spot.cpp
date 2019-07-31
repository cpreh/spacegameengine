//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/light/attenuation.hpp>
#include <sge/opengl/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/opengl/state/ffp/lighting/light/direction.hpp>
#include <sge/opengl/state/ffp/lighting/light/position.hpp>
#include <sge/opengl/state/ffp/lighting/light/spot.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot.hpp>
#include <fcppt/container/join.hpp>


sge::opengl::state::index_actor_vector
sge::opengl::state::ffp::lighting::light::spot(
	sge::renderer::state::ffp::lighting::light::spot const &_spot
)
{
	return
		fcppt::container::join(
			sge::opengl::state::index_actor_vector{
				sge::opengl::state::ffp::lighting::light::position(
					_spot.position()
				),
				sge::opengl::state::ffp::lighting::light::direction(
					_spot.direction()
				),
				sge::opengl::state::ffp::lighting::light::cutoff_angle(
					_spot.cutoff_angle()
				)
			},
			sge::opengl::state::ffp::lighting::light::attenuation(
				_spot.attenuation()
			)
		);
}
