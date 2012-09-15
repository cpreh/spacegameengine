/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/material/color.hpp>
#include <sge/opengl/state/ffp/lighting/material/float.hpp>
#include <sge/opengl/state/ffp/lighting/material/make_actors.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>
#include <fcppt/assign/make_container.hpp>


sge::opengl::state::actor_vector const
sge::opengl::state::ffp::lighting::material::make_actors(
	sge::renderer::state::ffp::lighting::material::parameters const &_parameters
)
{
	GLenum const face(
		GL_FRONT_AND_BACK
	);

	return
		fcppt::assign::make_container<
			sge::opengl::state::actor_vector
		>(
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_AMBIENT,
				_parameters.ambient().get()
			)
		)(
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_DIFFUSE,
				_parameters.diffuse().get()
			)
		)(
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_SPECULAR,
				_parameters.specular().get()
			)
		)(
			sge::opengl::state::ffp::lighting::material::color(
				face,
				GL_EMISSION,
				_parameters.emissive().get()
			)
		)(
			sge::opengl::state::ffp::lighting::material::float_(
				face,
				GL_SHININESS,
				static_cast<
					GLfloat
				>(
					_parameters.shininess().get()
				)
			)
		);
}
