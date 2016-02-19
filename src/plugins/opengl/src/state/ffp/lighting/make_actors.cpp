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


#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/make_actors.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/off_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::ffp::lighting::make_actors(
	sge::renderer::state::ffp::lighting::parameters const &_parameters
)
{
	return
		fcppt::variant::match(
			_parameters.variant(),
			[](
				sge::renderer::state::ffp::lighting::off const &
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							[]{
								return
									sge::opengl::disable(
										sge::opengl::convert::to_gl_enum<
											GL_LIGHTING
										>()
									);
							}
						}
					};
			},
			[](
				sge::renderer::state::ffp::lighting::enabled const &_enabled
			)
			{
				sge::image::color::rgba32f const ambient{
					sge::image::color::any::convert<
						sge::image::color::rgba32f_format
					>(
						_enabled.ambient_color().get()
					)
				};

				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							[]{
								return
									sge::opengl::enable(
										sge::opengl::convert::to_gl_enum<
											GL_LIGHTING
										>()
									);
							}
						},
						sge::opengl::state::wrap_error_handler<
							sge::opengl::state::actor
						>(
							[
								ambient
							]
							{
								sge::opengl::call(
									::glLightModelfv,
									sge::opengl::convert::to_gl_enum<
										GL_LIGHT_MODEL_AMBIENT
									>(),
									ambient.data()
								);
							},
							FCPPT_TEXT("glLightModelfv")
						),
						sge::opengl::state::actor{
							std::bind(
								sge::opengl::enable_bool,
								sge::opengl::convert::to_gl_enum<
									GL_COLOR_MATERIAL
								>(),
								_enabled.diffuse_from_vertex().get()
							)
						}
					};
			}
		);
}
