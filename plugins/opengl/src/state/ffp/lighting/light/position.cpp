//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/ffp/lighting/light/position.hpp>
#include <sge/opengl/state/ffp/lighting/light/position_impl.hpp>
#include <sge/renderer/state/ffp/lighting/light/position.hpp>
#include <fcppt/math/vector/push_back.hpp>


sge::opengl::state::index_actor
sge::opengl::state::ffp::lighting::light::position(
	sge::renderer::state::ffp::lighting::light::position const &_position
)
{
	return
		sge::opengl::state::ffp::lighting::light::position_impl(
			fcppt::math::vector::push_back(
				_position.get(),
				1.F
			)
		);
}
