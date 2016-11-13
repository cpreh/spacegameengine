/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/get_fun_ref.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/core/blend/alpha.hpp>
#include <sge/opengl/state/core/blend/make_actors.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::blend::make_actors(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::blend::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::core::blend::alpha(
				_context,
				_parameters.alpha_variant()
			),
			sge::opengl::state::actor_vector{
				sge::opengl::state::wrap_error_handler<
					sge::opengl::state::actor
				>(
					std::bind(
						sge::opengl::get_fun_ref(
							::glColorMask
						),
						_parameters.write_mask().write_red().get(),
						_parameters.write_mask().write_green().get(),
						_parameters.write_mask().write_blue().get(),
						_parameters.write_mask().write_alpha().get()
					),
					FCPPT_TEXT("glColorMask")
				)
			}
		);
}
