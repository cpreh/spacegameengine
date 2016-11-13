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
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/get_fun_ref.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/depth_func.hpp>
#include <sge/opengl/state/core/depth_stencil/depth/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/depth/write_enable.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/off_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::depth_stencil::depth::make_actors(
	sge::renderer::state::core::depth_stencil::depth::variant const &_variant
)
{
	return
		fcppt::variant::match(
			_variant,
			[](
				sge::renderer::state::core::depth_stencil::depth::off const &
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::disable,
								GL_DEPTH_TEST
							)
						},
						sge::opengl::state::core::depth_stencil::depth::write_enable(
							sge::renderer::state::core::depth_stencil::depth::write_enable(
								true
							)
						)
					};
			},
			[](
				sge::renderer::state::core::depth_stencil::depth::enabled const &_enabled
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::enable,
								GL_DEPTH_TEST
							)
						},
						sge::opengl::state::wrap_error_handler<
							sge::opengl::state::actor
						>(
							std::bind(
								sge::opengl::get_fun_ref(
									::glDepthFunc
								),
								sge::opengl::state::convert::depth_func(
									_enabled.func()
								)
							),
							FCPPT_TEXT("glDepthFunc")
						),
						sge::opengl::state::core::depth_stencil::depth::write_enable(
							_enabled.write_enable()
						)
					};
			}
		);
}
