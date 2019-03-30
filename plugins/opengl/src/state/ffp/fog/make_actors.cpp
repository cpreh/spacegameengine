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


#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/fog_mode.hpp>
#include <sge/opengl/state/ffp/fog/color.hpp>
#include <sge/opengl/state/ffp/fog/float.hpp>
#include <sge/opengl/state/ffp/fog/make_actors.hpp>
#include <sge/renderer/state/ffp/fog/enabled.hpp>
#include <sge/renderer/state/ffp/fog/off_fwd.hpp>
#include <sge/renderer/state/ffp/fog/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::fog::make_actors(
	sge::renderer::state::ffp::fog::parameters const &_parameters
)
{
	return
		fcppt::variant::match(
			_parameters.variant(),
			[](
				sge::renderer::state::ffp::fog::off const &
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							[]{
								return
									sge::opengl::disable(
										GL_FOG
									);
							}
						}
					};
			},
			[](
				sge::renderer::state::ffp::fog::enabled const &_enabled
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							[]{
								return
									sge::opengl::enable(
										GL_FOG
									);
							}
						},
						sge::opengl::state::wrap_error_handler<
							sge::opengl::state::actor
						>(
							[
								_enabled
							]{
								return
									sge::opengl::call(
										::glFogi,
										sge::opengl::convert::to_gl_enum<
											GL_FOG_MODE
										>(),
										sge::opengl::state::convert::fog_mode(
											_enabled.mode()
										)
									);
							},
							FCPPT_TEXT("glFogi")
						),
						sge::opengl::state::ffp::fog::float_(
							GL_FOG_START,
							_enabled.start().get()
						),
						sge::opengl::state::ffp::fog::float_(
							GL_FOG_END,
							_enabled.end().get()
						),
						sge::opengl::state::ffp::fog::float_(
							GL_FOG_DENSITY,
							_enabled.density().get()
						),
						sge::opengl::state::ffp::fog::color(
							_enabled.color()
						)
					};
			}
		);
}
