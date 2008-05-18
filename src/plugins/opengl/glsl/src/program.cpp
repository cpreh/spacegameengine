/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../program.hpp"
#include <sge/exception.hpp>
#include <boost/foreach.hpp>

//namespace
//{

template<typename Handle>
Handle create_program();

template<typename Handle>
GLenum vertex_shader_type();

template<typename Handle>
GLenum pixel_shader_type();

template<typename Handle>
GLenum detach_shader(
	Handle program,
	Handle shader);

template<typename Handle>
GLenum delete_program(
	Handle program);

template<typename Handle>
void attach_shader(
	Handle program,
	Handle shader);

template<typename Handle>
void link_program(
	Handle program);

template<typename Handle>
GLenum get_link_status(
	Handle program);

template<typename Handle>
void use_program(
	Handle program);

//}

template<typename Handle>
sge::ogl::glsl::program<Handle>::program(
	std::string const &vs_source,
	std::string const &ps_source)
: id_(glCreateProgram())
//: id_(create_program<Handle>())
{
	attach_shader(
		shader_ptr(
			new shader<Handle>(
				GL_VERTEX_SHADER,
				vs_source)));
	attach_shader(
		shader_ptr(
			new shader<Handle>(
				GL_FRAGMENT_SHADER,
				ps_source)));
	link();
}

template<typename Handle>
sge::ogl::glsl::program<Handle>::~program()
{
	BOOST_FOREACH(shader_ptr &s, shaders)
		glDetachShader(id(), s->id());
	glDeleteProgram(id());
}

template<typename Handle>
void sge::ogl::glsl::program<Handle>::attach_shader(
	const shader_ptr s)
{
	glAttachShader(id(), s->id());
	shaders.push_back(s);
}

template<typename Handle>
void sge::ogl::glsl::program<Handle>::link()
{
	glLinkProgram(id());

	int link_status;
	glGetProgramiv(id(), GL_LINK_STATUS, &link_status);
	if(link_status == GL_FALSE)
		throw exception(SGE_TEXT("Linking a program failed!"));
}

template<typename Handle>
void sge::ogl::glsl::program<Handle>::use()
{
	glUseProgram(id());
}

template<typename Handle>
sge::glsl::uniform_variable_ptr
sge::ogl::glsl::program<Handle>::uniform(const std::string& name)
{
	return sge::glsl::uniform_variable_ptr(new uniform_variable<Handle>(id(), name));
}

template<typename Handle>
sge::glsl::attribute_variable_ptr
sge::ogl::glsl::program<Handle>::attribute(const std::string& name)
{
	return sge::glsl::attribute_variable_ptr(new attribute_variable<Handle>(id(), name));
}

template<typename Handle>
void sge::ogl::glsl::program<Handle>::use_ffp()
{
	use_program<Handle>(0);
	//glUseProgram(0);
}

template<typename Handle>
Handle sge::ogl::glsl::program<Handle>::id() const
{
	return id_;
}

template class sge::ogl::glsl::program<GLuint>;
//template class sge::ogl::glsl::program<GLhandleARB>;
