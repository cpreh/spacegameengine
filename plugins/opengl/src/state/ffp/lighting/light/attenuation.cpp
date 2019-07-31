//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/light/attenuation.hpp>
#include <sge/opengl/state/ffp/lighting/light/float.hpp>
#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>


sge::opengl::state::index_actor_vector
sge::opengl::state::ffp::lighting::light::attenuation(
	sge::renderer::state::ffp::lighting::light::attenuation const &_attenuation
)
{
	return
		sge::opengl::state::index_actor_vector{
			sge::opengl::state::ffp::lighting::light::float_(
				GL_CONSTANT_ATTENUATION,
				_attenuation.constant().get()
			),
			sge::opengl::state::ffp::lighting::light::float_(
				GL_LINEAR_ATTENUATION,
				_attenuation.linear().get()
			),
			sge::opengl::state::ffp::lighting::light::float_(
				GL_QUADRATIC_ATTENUATION,
				_attenuation.quadratic().get()
			)
		};
}
