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
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/enabled_variant.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask_all.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::depth_stencil::stencil::make_actors(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::depth_stencil::stencil::variant const &_variant
)
{
	return
		fcppt::variant::match(
			_variant,
			[](
				sge::renderer::state::core::depth_stencil::stencil::off const &
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::disable,
								GL_STENCIL_TEST
							)
						},
						sge::opengl::state::core::depth_stencil::stencil::write_mask(
							sge::renderer::state::core::depth_stencil::stencil::write_mask_all()
						)
					};
			},
			[
				&_context
			](
				sge::renderer::state::core::depth_stencil::stencil::enabled const &_enabled
			)
			{
				return
					fcppt::container::join(
						sge::opengl::state::actor_vector{
							sge::opengl::state::actor{
								std::bind(
									sge::opengl::enable,
									GL_STENCIL_TEST
								)
							}
						},
						sge::opengl::state::core::depth_stencil::stencil::enabled_variant(
							_context,
							_enabled.ref(),
							_enabled.read_mask(),
							_enabled.write_mask(),
							_enabled.enabled_variant()
						)
					);
			}
		);
}
