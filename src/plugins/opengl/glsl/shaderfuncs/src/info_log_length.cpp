/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../info_log_length.hpp"
#include "../get_integer.hpp"
#include "../../shader_contexts.hpp"
#include "../../instantiate.hpp"

template<
	typename Environment
>
GLint
sge::opengl::glsl::shaderfuncs::info_log_length(
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
			_context.info_log_length_type()
		);
}

#define SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_INFO_LOG_LENGTH(\
	env\
)\
template \
GLint \
sge::opengl::glsl::shaderfuncs::info_log_length<\
	env\
>(\
	env::shader_context const &,\
	env::handle\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_INFO_LOG_LENGTH
)
