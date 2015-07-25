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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/texture/cube_config.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/optional_cube_config.hpp>
#include <sge/opengl/texture/convert/make_buffer_type.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

sge::opengl::texture::cube_side_array const normal_sides{{{
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	)
}}};

sge::opengl::texture::cube_side_array const arb_sides{{{
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB
	)
}}};

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::texture::cube_context::cube_context()
:
	sge::opengl::context::system::base(),
	config_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_1_3
		)
		?
			sge::opengl::texture::optional_cube_config(
				sge::opengl::texture::cube_config(
					sge::opengl::texture::convert::make_type(
						GL_TEXTURE_CUBE_MAP
					),
					::normal_sides
				)
			)
		:
			sge::opengl::convert::from_gl_bool(
				GLEW_ARB_texture_cube_map
			)
			?
				sge::opengl::texture::optional_cube_config(
					sge::opengl::texture::cube_config(
						sge::opengl::texture::convert::make_type(
							GL_TEXTURE_CUBE_MAP_ARB
						),
						::arb_sides
					)
				)
			:
				sge::opengl::texture::optional_cube_config()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::texture::cube_context::~cube_context()
{
}

sge::opengl::texture::optional_cube_config const &
sge::opengl::texture::cube_context::config() const
{
	return
		config_;
}

sge::opengl::context::system::id const
sge::opengl::texture::cube_context::static_id(
	sge::opengl::context::system::make_id()
);
