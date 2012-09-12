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


#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/lighting/light/color.hpp>
#include <sge/opengl/state/ffp/lighting/light/make_actors.hpp>
#include <sge/opengl/state/ffp/lighting/light/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::opengl::state::index_actor_vector const
sge::opengl::state::ffp::lighting::light::make_actors(
	sge::renderer::state::ffp::lighting::light::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			fcppt::assign::make_container<
				sge::opengl::state::index_actor_vector
			>(
				sge::opengl::state::ffp::lighting::light::color(
					GL_AMBIENT,
					_parameters.ambient().get()
				)
			)(
				sge::opengl::state::ffp::lighting::light::color(
					GL_DIFFUSE,
					_light.diffuse().get()
				)
			)(
				sge::opengl::state::ffp::lighting::light::color(
					GL_SPECULAR,
					_light.specular().get()
				)
			)
		)(
			fcppt::variant::apply_unary(
				sge::opengl::state::ffp::lighting::light::visitor(),
				_parameters.variant()
			)
		);
}
