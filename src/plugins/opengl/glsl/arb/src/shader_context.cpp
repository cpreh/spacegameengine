
/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../shader_context.hpp"
#include "../../../context/make_id.hpp"
#include "../../../common.hpp"

sge::opengl::glsl::arb::shader_context::shader_context()
:
	create_shader_(
		glCreateShaderObjectARB
	),
	delete_shader_(
		glDeleteObjectARB
	),
	compile_shader_(
		glCompileShaderARB
	),
	shader_source_(
		glShaderSourceARB
	),
	shader_integer_(
		glGetObjectParameterivARB
	),
	shader_info_log_(
		glGetInfoLogARB
	),
	vertex_shader_type_(
		GL_VERTEX_SHADER_ARB
	),
	pixel_shader_type_(
		GL_FRAGMENT_SHADER_ARB
	),
	compile_status_type_(
		GL_OBJECT_COMPILE_STATUS_ARB
	),
	info_log_length_type_(
		GL_OBJECT_INFO_LOG_LENGTH_ARB
	)
{}

sge::opengl::glsl::arb::shader_context::~shader_context()
{}

sge::opengl::glsl::arb::shader_context::gl_create_shader
sge::opengl::glsl::arb::shader_context::create_shader() const
{
	return create_shader_;
}
	
sge::opengl::glsl::arb::shader_context::gl_delete_shader
sge::opengl::glsl::arb::shader_context::delete_shader() const
{
	return delete_shader_;
}

sge::opengl::glsl::arb::shader_context::gl_compile_shader
sge::opengl::glsl::arb::shader_context::compile_shader() const
{
	return compile_shader_;
}

sge::opengl::glsl::arb::shader_context::gl_shader_source
sge::opengl::glsl::arb::shader_context::shader_source() const
{
	return shader_source_;
}

sge::opengl::glsl::arb::shader_context::gl_shader_integer
sge::opengl::glsl::arb::shader_context::shader_integer() const
{
	return shader_integer_;
}

sge::opengl::glsl::arb::shader_context::gl_shader_info_log
sge::opengl::glsl::arb::shader_context::shader_info_log() const
{
	return shader_info_log_;
}


GLenum
sge::opengl::glsl::arb::shader_context::vertex_shader_type() const
{
	return vertex_shader_type_;
}

GLenum
sge::opengl::glsl::arb::shader_context::pixel_shader_type() const
{
	return pixel_shader_type_;
}

sge::opengl::context::id const
sge::opengl::glsl::arb::shader_context::static_id(
	sge::opengl::context::make_id()
);
