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
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <boost/array.hpp>
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
				vertex_shader_type<Native>(),
				vs_source)));
	attach_shader(
		shader_ptr(
			new shader<Native>(
				pixel_shader_type<Native>(),
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

	if(get_link_status<Native>(id()) == GL_FALSE)
	{
		typedef boost::array<char, 1024> errorlog_array;
		errorlog_array errorlog;

		GLint len;
		get_program_info_log<Native>(
			id(),
			static_cast<GLint>(errorlog.size() - 1u),
			&len,
			errorlog.c_array());
		if(static_cast<errorlog_array::size_type>(len) >= errorlog.size())
			throw exception(SGE_TEXT("GLSL link info too big!"));
		errorlog[len] = '\0';
		throw exception(
			string(SGE_TEXT("Linking a program failed!"))
			+ iconv(errorlog.data()));
	}
}

template<bool Native>
void sge::ogl::glsl::program<Native>::use()
{
	use_program<Native>(id());
}

template<bool Native>
void sge::ogl::glsl::program<Native>::use(
	const renderer::glsl::program_ptr p)
{
	if(!p)
	{
		use_ffp();
		return;
	}

	dynamic_pointer_cast<program<Native> >(p)->use();
}

template<bool Native>
const sge::renderer::glsl::uniform_variable_ptr
sge::ogl::glsl::program<Native>::uniform(const std::string& name)
{
	return renderer::glsl::uniform_variable_ptr(
		new uniform_variable<Native>(id(), name));
}

template<bool Native>
const sge::renderer::glsl::attribute_variable_ptr
sge::ogl::glsl::program<Native>::attribute(const std::string& name)
{
	return renderer::glsl::attribute_variable_ptr(
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
