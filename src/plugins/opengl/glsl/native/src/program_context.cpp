/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../program_context.hpp"
#include "../../../context/make_id.hpp"
#include "../../../common.hpp"

sge::opengl::glsl::native::program_context::program_context()
:
	create_program_(
		glCreateProgram
	),
	delete_program_(
		glDeleteProgram
	),
	attach_shader_(
		glAttachShader
	),
	detach_shader_(
		glDetachShader
	),
	link_program_(
		glLinkProgram
	),
	program_integer_(
		glGetProgramiv
	),
	use_program_(
		glUseProgram
	),
	program_info_log_(
		glGetProgramInfoLog
	),
	get_attrib_location_(
		glGetAttribLocation
	),
	link_status_type_(
		GL_LINK_STATUS
	),
	info_log_length_type_(
		GL_INFO_LOG_LENGTH
	)
{}

sge::opengl::glsl::native::program_context::~program_context()
{}

sge::opengl::glsl::native::program_context::gl_create_program
sge::opengl::glsl::native::program_context::create_program() const
{
	return create_program_;
}

sge::opengl::glsl::native::program_context::gl_delete_program
sge::opengl::glsl::native::program_context::delete_program() const
{
	return delete_program_;
}

sge::opengl::glsl::native::program_context::gl_attach_shader
sge::opengl::glsl::native::program_context::attach_shader() const
{
	return attach_shader_;
}

sge::opengl::glsl::native::program_context::gl_detach_shader
sge::opengl::glsl::native::program_context::detach_shader() const
{
	return detach_shader_;
}

sge::opengl::glsl::native::program_context::gl_link_program
sge::opengl::glsl::native::program_context::link_program() const
{
	return link_program_;
}

sge::opengl::glsl::native::program_context::gl_program_integer
sge::opengl::glsl::native::program_context::program_integer() const
{
	return program_integer_;
}

sge::opengl::glsl::native::program_context::gl_use_program
sge::opengl::glsl::native::program_context::use_program() const
{
	return use_program_;
}

sge::opengl::glsl::native::program_context::gl_program_info_log
sge::opengl::glsl::native::program_context::program_info_log() const
{
	return program_info_log_;
}

sge::opengl::glsl::native::program_context::gl_get_attrib_location
sge::opengl::glsl::native::program_context::get_attrib_location() const
{
	return get_attrib_location_;
}

GLenum
sge::opengl::glsl::native::program_context::link_status_type() const
{
	return link_status_type_;
}

GLenum
sge::opengl::glsl::native::program_context::info_log_length_type() const
{
	return info_log_length_type_;
}

sge::opengl::context::id const
sge::opengl::glsl::native::program_context::static_id(
	sge::opengl::context::make_id()
);
