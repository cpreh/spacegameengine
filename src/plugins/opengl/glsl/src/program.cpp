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
#include "../program_functions.hpp"
#include "../../error.hpp"
#include <sge/exception.hpp>
#include <boost/foreach.hpp>

template<bool Native>
sge::ogl::glsl::program<Native>::program(
	std::string const &vs_source,
	std::string const &ps_source)
: id_(create_program<Native>())
{
	attach_shader(
		shader_ptr(
			new shader<Native>(
				GL_VERTEX_SHADER,
				vs_source)));
	attach_shader(
		shader_ptr(
			new shader<Native>(
				GL_FRAGMENT_SHADER,
				ps_source)));
	link();
}

template<bool Native>
sge::ogl::glsl::program<Native>::~program()
{
	BOOST_FOREACH(shader_ptr &s, shaders)
		detach_shader<Native>(id(), s->id());
	delete_program<Native>(id());
}

template<bool Native>
void sge::ogl::glsl::program<Native>::attach_shader(
	const shader_ptr s)
{
	glsl::attach_shader<Native>(id(), s->id());
	shaders.push_back(s);
}

template<bool Native>
void sge::ogl::glsl::program<Native>::link()
{
	link_program<Native>(id());
	//glLinkProgram(id());

//	if(get_program_integer<Native>(id()) == GL_FALSE)
//		throw exception(SGE_TEXT("Linking a program failed!"));
		
//	int link_status;
//	glGetProgramiv(id(), GL_LINK_STATUS, &link_status);
//	if(link_status == GL_FALSE)
//		throw exception(SGE_TEXT("Linking a program failed!"));
}

template<bool Native>
void sge::ogl::glsl::program<Native>::use()
{
	use_program<Native>(id());
	//glUseProgram(id());
}

template<bool Native>
void sge::ogl::glsl::program<Native>::use(
	const sge::glsl::program_ptr p)
{
	if(!p)
	{
		use_ffp();
		return;
	}

	dynamic_pointer_cast<program<Native> >(p)->use();
}

template<bool Native>
sge::glsl::uniform_variable_ptr
sge::ogl::glsl::program<Native>::uniform(const std::string& name)
{
	return sge::glsl::uniform_variable_ptr(
		new uniform_variable<Native>(id(), name));
}

template<bool Native>
sge::glsl::attribute_variable_ptr
sge::ogl::glsl::program<Native>::attribute(const std::string& name)
{
	return sge::glsl::attribute_variable_ptr(
		new attribute_variable<Native>(id(), name));
}

template<bool Native>
void sge::ogl::glsl::program<Native>::use_ffp()
{
	use_program<Native>(0);
	//glUseProgram(0);
}

template<bool Native>
typename sge::ogl::glsl::traits<Native>::handle
sge::ogl::glsl::program<Native>::id() const
{
	return id_;
}

template class sge::ogl::glsl::program<true>;
template class sge::ogl::glsl::program<false>;
