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


#include "../shader.hpp"
#include "../shader_functions.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <boost/array.hpp>

template<bool Native>
sge::ogl::glsl::shader<Native>::shader(
	GLenum const type,
	renderer::glsl::string const &source)
: id_(create_shader<Native>(type))
{
	const char* const ptr = source.c_str();
	const GLint len = static_cast<GLint>(source.size());
	shader_source<Native>(id(), 1, const_cast<const char**>(&ptr), &len);

	compile_shader<Native>(id());
	
	if(get_compile_status<Native>(id()) == GL_FALSE)
	{
		typedef boost::array<char, 1024> errorlog_array;
		errorlog_array errorlog;

		GLint len;
		get_shader_info_log<Native>(
			id(),
			static_cast<GLint>(errorlog.size() - 1u),
			&len,
			errorlog.c_array());
		if(static_cast<errorlog_array::size_type>(len) >= errorlog.size())
			throw exception(SGE_TEXT("GLSL compile info too big!"));
		errorlog[len] = '\0';
		throw exception(
			string(SGE_TEXT("Compiling a shader failed!\n"))
			+ iconv(errorlog.data()));
	}
}

template<bool Native>
sge::ogl::glsl::shader<Native>::~shader()
{
	delete_shader<Native>(id());
}

template<bool Native>
typename sge::ogl::glsl::traits<Native>::handle
sge::ogl::glsl::shader<Native>::id() const
{
	return id_;
}

template class sge::ogl::glsl::shader<true>;
template class sge::ogl::glsl::shader<false>;
