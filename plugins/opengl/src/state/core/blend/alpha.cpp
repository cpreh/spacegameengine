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
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/core/blend/alpha.hpp>
#include <sge/opengl/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled_fwd.hpp>
#include <sge/renderer/state/core/blend/alpha_off_fwd.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::blend::alpha(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::blend::alpha_variant const &_variant
)
{
	return
		fcppt::variant::match(
			_variant,
			[](
				sge::renderer::state::core::blend::alpha_off const &
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::disable,
								GL_BLEND
							)
						}
					};
			},
			[
				&_context
			](
				sge::renderer::state::core::blend::alpha_enabled const &_enabled
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::enable,
								GL_BLEND
							)
						},
						sge::opengl::state::core::blend::alpha_enabled(
							_context,
							_enabled
						)
					};
			}
		);
}
