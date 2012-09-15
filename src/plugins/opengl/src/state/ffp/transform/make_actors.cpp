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
#include <sge/opengl/matrix_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/ffp/transform/actor_vector.hpp>
#include <sge/opengl/state/ffp/transform/make_actors.hpp>
#include <sge/opengl/state/ffp/transform/set_matrix_and_mode.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/tr1/functional.hpp>


sge::opengl::state::ffp::transform::actor_vector const
sge::opengl::state::ffp::transform::make_actors(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::state::ffp::transform::parameters const &_parameters
)
{
	return
		fcppt::assign::make_container<
			sge::opengl::state::ffp::transform::actor_vector
		>(
			std::tr1::bind(
				&sge::opengl::state::ffp::transform::set_matrix_and_mode,
				fcppt::ref(
					_system_context
				),
				std::tr1::placeholders::_1,
				sge::opengl::context::use<
					sge::opengl::matrix_context
				>(
					_system_context
				).have_transpose()
				?
					_parameters.matrix()
				:
					fcppt::math::matrix::transpose(
						_parameters.matrix()
					)
			)
		);
}
