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
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/point_sprite_context.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::point_sprite_context::point_sprite_context()
:
	sge::opengl::context::system::base(),
	is_native_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_2_0
		)
	),
	is_arb_(
		sge::opengl::convert::from_gl_bool(
			GLEW_ARB_point_sprite
		)
	),
	point_sprite_flag_(
		is_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_POINT_SPRITE
				)
			)
		:
			is_arb_
			?
				sge::opengl::optional_enum(
					static_cast<
						GLenum
					>(
						GL_POINT_SPRITE_ARB
					)

				)
			:
				sge::opengl::optional_enum()
	),
	vertex_shader_size_flag_(
		is_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_VERTEX_PROGRAM_POINT_SIZE
				)
			)
		:
			is_arb_
			?
				sge::opengl::optional_enum(
					static_cast<
						GLenum
					>(
						GL_VERTEX_PROGRAM_POINT_SIZE_ARB
					)
				)
			:
				sge::opengl::optional_enum()
	),
	coord_replace_flag_(
		is_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_COORD_REPLACE
				)
			)
		:
			is_arb_
			?
				sge::opengl::optional_enum(
					static_cast<
						GLenum
					>(
						GL_COORD_REPLACE_ARB
					)
				)
			:
				sge::opengl::optional_enum()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::point_sprite_context::~point_sprite_context()
{
}

bool
sge::opengl::point_sprite_context::is_supported() const
{
	return
		is_native_
		|| is_arb_;
}

sge::opengl::optional_enum const
sge::opengl::point_sprite_context::point_sprite_flag() const
{
	return point_sprite_flag_;
}

sge::opengl::optional_enum const
sge::opengl::point_sprite_context::vertex_shader_size_flag() const
{
	return vertex_shader_size_flag_;
}

sge::opengl::optional_enum const
sge::opengl::point_sprite_context::coord_replace_flag() const
{
	return coord_replace_flag_;
}

sge::opengl::context::system::id const
sge::opengl::point_sprite_context::static_id(
	sge::opengl::context::system::make_id()
);
