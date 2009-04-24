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



#ifndef SGE_OPENGL_GLSL_PROGRAM_ARBHPP_INCLUDED
#define SGE_OPENGL_GLSL_PROGRAM_ARB_HPP_INCLUDED

#include "../common.hpp"
#include "program_functions.hpp"
#include "traits.hpp"

namespace sge
{
namespace ogl
{
namespace glsl
{

template<>
traits<false>::handle create_program<false>();

template<>
GLenum vertex_shader_type<false>();

template<>
GLenum pixel_shader_type<false>();

template<>
void detach_shader<false>(
	traits<false>::handle program,
	traits<false>::handle shader);

template<>
void delete_program<false>(
	traits<false>::handle program);

template<>
void attach_shader<false>(
	traits<false>::handle program,
	traits<false>::handle shader);

template<>
void link_program<false>(
	traits<false>::handle program);

template<>
GLint program_integer<false>(
	GLenum what,
	traits<false>::handle program);

template<>
GLint link_status<false>(
	traits<false>::handle program);

template<>
void use_program<false>(
	traits<false>::handle program);

template<>
void program_info_log<false>(
	traits<false>::handle program,
	GLint maxlen,
	GLint *len,
	char *data);

}
}
}

#endif
