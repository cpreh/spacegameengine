/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/state/ffp/lighting/light/color.hpp>
#include <sge/opengl/state/ffp/lighting/light/directional.hpp>
#include <sge/opengl/state/ffp/lighting/light/make_actors.hpp>
#include <sge/opengl/state/ffp/lighting/light/point.hpp>
#include <sge/opengl/state/ffp/lighting/light/spot.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::state::index_actor_vector
sge::opengl::state::ffp::lighting::light::make_actors(
	sge::renderer::state::ffp::lighting::light::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::index_actor_vector{
				sge::opengl::state::ffp::lighting::light::color(
					GL_AMBIENT,
					_parameters.ambient().get()
				),
				sge::opengl::state::ffp::lighting::light::color(
					GL_DIFFUSE,
					_parameters.diffuse().get()
				),
				sge::opengl::state::ffp::lighting::light::color(
					GL_SPECULAR,
					_parameters.specular().get()
				)
			},
			fcppt::variant::match(
				_parameters.variant(),
				&sge::opengl::state::ffp::lighting::light::directional,
				&sge::opengl::state::ffp::lighting::light::point,
				&sge::opengl::state::ffp::lighting::light::spot
			)
		);
}
