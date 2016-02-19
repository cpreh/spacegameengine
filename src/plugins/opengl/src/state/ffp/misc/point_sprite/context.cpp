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
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/context.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/optional_config.hpp>


sge::opengl::state::ffp::misc::point_sprite::context::context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				2u
			},
			sge::opengl::info::minor_version{
				0u
			}
		)
		?
			sge::opengl::state::ffp::misc::point_sprite::optional_config(
				sge::opengl::state::ffp::misc::point_sprite::config(
					// TODO: Move all strong typedefs out of the class
					sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag_type(
						sge::opengl::convert::to_gl_enum<
							GL_POINT_SPRITE
						>()
					),
					sge::opengl::state::ffp::misc::point_sprite::config::vertex_shader_size_flag_type(
						sge::opengl::convert::to_gl_enum<
							GL_VERTEX_PROGRAM_POINT_SIZE
						>()
					),
					sge::opengl::state::ffp::misc::point_sprite::config::coord_replace_flag_type(
						sge::opengl::convert::to_gl_enum<
							GL_COORD_REPLACE
						>()
					)
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"ARB_point_sprite"
				}
			)
			?
				sge::opengl::state::ffp::misc::point_sprite::optional_config(
					sge::opengl::state::ffp::misc::point_sprite::config(
						sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag_type(
							sge::opengl::convert::to_gl_enum<
								GL_POINT_SPRITE_ARB
							>()
						),
						sge::opengl::state::ffp::misc::point_sprite::config::vertex_shader_size_flag_type(
							sge::opengl::convert::to_gl_enum<
								GL_VERTEX_PROGRAM_POINT_SIZE_ARB
							>()
						),
						sge::opengl::state::ffp::misc::point_sprite::config::coord_replace_flag_type(
							sge::opengl::convert::to_gl_enum<
								GL_COORD_REPLACE_ARB
							>()
						)
					)
				)
			:
				sge::opengl::state::ffp::misc::point_sprite::optional_config()
	)
{
}

sge::opengl::state::ffp::misc::point_sprite::context::~context()
{
}

sge::opengl::state::ffp::misc::point_sprite::optional_config const &
sge::opengl::state::ffp::misc::point_sprite::context::config() const
{
	return
		config_;
}

sge::opengl::context::id const
sge::opengl::state::ffp::misc::point_sprite::context::static_id(
	sge::opengl::context::make_id()
);
