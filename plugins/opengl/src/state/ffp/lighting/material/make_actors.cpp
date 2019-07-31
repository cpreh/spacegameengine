//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/material/color.hpp>
#include <sge/opengl/state/ffp/lighting/material/float.hpp>
#include <sge/opengl/state/ffp/lighting/material/make_actors.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>
#include <fcppt/cast/size.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::lighting::material::make_actors(
	sge::renderer::state::ffp::lighting::material::parameters const &_parameters
)
{
	GLenum const face(
		GL_FRONT_AND_BACK
	);

	return
		sge::opengl::state::actor_vector{
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_AMBIENT,
				_parameters.ambient().get()
			),
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_DIFFUSE,
				_parameters.diffuse().get()
			),
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_SPECULAR,
				_parameters.specular().get()
			),
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_EMISSION,
				_parameters.emissive().get()
			),
			sge::opengl::state::ffp::lighting::material::float_(
				face,
				GL_SHININESS,
				fcppt::cast::size<
					GLfloat
				>(
					_parameters.shininess().get()
				)
			)
		};
}
