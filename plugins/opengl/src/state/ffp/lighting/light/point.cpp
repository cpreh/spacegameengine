//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/light/attenuation.hpp>
#include <sge/opengl/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/opengl/state/ffp/lighting/light/point.hpp>
#include <sge/opengl/state/ffp/lighting/light/position.hpp>
#include <sge/renderer/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/renderer/state/ffp/lighting/light/point.hpp>
#include <fcppt/container/join.hpp>


sge::opengl::state::index_actor_vector
sge::opengl::state::ffp::lighting::light::point(
	sge::renderer::state::ffp::lighting::light::point const &_point
)
{
	return
		fcppt::container::join(
			sge::opengl::state::index_actor_vector{
				sge::opengl::state::ffp::lighting::light::position(
					_point.position()
				),
				// special value to make this a point light
				sge::opengl::state::ffp::lighting::light::cutoff_angle(
					sge::renderer::state::ffp::lighting::light::cutoff_angle(
						180.f
					)
				)
			},
			sge::opengl::state::ffp::lighting::light::attenuation(
				_point.attenuation()
			)
		);
}
