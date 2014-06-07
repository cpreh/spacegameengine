/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
