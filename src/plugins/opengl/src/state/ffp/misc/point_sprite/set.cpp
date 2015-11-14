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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config_fwd.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/context.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/set_impl.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::misc::point_sprite::set(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::misc::enable_point_sprites const _enable
)
{
	return
		fcppt::maybe(
			sge::opengl::context::use<
				sge::opengl::state::ffp::misc::point_sprite::context
			>(
				_context,
				_context.info()
			).config(),
			[
				_enable
			]{
				if(
					!_enable.get()
				)
					return
						sge::opengl::state::actor_vector();

				throw
					sge::renderer::unsupported{
						FCPPT_TEXT("GL_POINT_SPRITE"),
						FCPPT_TEXT("opengl-2.0"),
						FCPPT_TEXT("ARB_point_sprite")
					};
			},
			[
				&_context,
				_enable
			](
				sge::opengl::state::ffp::misc::point_sprite::config const &_config
			)
			{
				return
					sge::opengl::state::ffp::misc::point_sprite::set_impl(
						_context,
						_config,
						_enable
					);
			}
		);
}
