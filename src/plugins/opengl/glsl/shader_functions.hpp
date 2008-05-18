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


#ifndef SGE_OPENGL_GLSL_SHADER_FUNCTIONS_HPP_INCLUDED
#define SGE_OPENGL_GLSL_SHADER_FUNCTIONS_HPP_INCLUDED

#include "traits.hpp"
#include "../common.hpp"

namespace sge
{
namespace ogl
{
namespace glsl
{

template<bool Native>
typename traits<Native>::handle create_shader(
	GLenum type);

template<bool Native>
void shader_source(
	typename traits<Native>::handle shader,
	GLint num_strings,
	char const **strings,
	GLint const *len_of_strings);

template<bool Native>
void compile_shader(
	typename traits<Native>::handle shader);

template<bool Native>
GLint get_shader_integer(
	GLenum what,
	typename traits<Native>::handle shader);

template<bool Native>
GLint get_compile_status(
	typename traits<Native>::handle shader);

template<bool Native>
void get_shader_info_log(
	typename traits<Native>::handle program,
	GLint maxlen,
	GLint *len,
	char *data);

template<bool Native>
void delete_shader(
	typename traits<Native>::handle shader);

}
}
}

#endif
