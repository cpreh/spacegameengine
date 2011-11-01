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


#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/glsl/shader_contexts.hpp>
#include <sge/opengl/glsl/shaderfuncs/compile_status.hpp>
#include <sge/opengl/glsl/shaderfuncs/get_integer.hpp>


template<
	typename Environment
>
GLint
sge::opengl::glsl::shaderfuncs::compile_status(
	typename Environment::shader_context const &_context,
	typename Environment::handle const _handle
)
{
	return
		shaderfuncs::get_integer<
			Environment
		>(
			_context,
			_handle,
			_context.compile_status_type()
		);
}

#define SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_COMPILE_STATUS(\
	env\
)\
template \
GLint \
sge::opengl::glsl::shaderfuncs::compile_status<\
	env\
>(\
	env::shader_context const &,\
	env::handle\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_COMPILE_STATUS
)
