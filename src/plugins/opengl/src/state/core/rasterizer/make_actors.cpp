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
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/core/rasterizer/cull_mode.hpp>
#include <sge/opengl/state/core/rasterizer/fill_mode.hpp>
#include <sge/opengl/state/core/rasterizer/make_actors.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/tr1/functional.hpp>


sge::opengl::state::actor_vector const
sge::opengl::state::core::rasterizer::make_actors(
	sge::renderer::state::core::rasterizer::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::core::rasterizer::cull_mode(
				_parameters.cull_mode()
			),
			fcppt::assign::make_container<
				sge::opengl::state::actor_vector
			>(
				sge::opengl::state::core::rasterizer::fill_mode(
					_parameters.fill_mode()
				)
			)(
				std::tr1::bind(
					sge::opengl::enable_bool,
					GL_SCISSOR_TEST,
					_parameters.enable_scissor_test().get()
				)
			)
			.container()
		);
}
