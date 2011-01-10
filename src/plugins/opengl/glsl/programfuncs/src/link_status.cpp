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


#include "../link_status.hpp"
#include "../get_integer.hpp"
#include "../../program_contexts.hpp"
#include "../../instantiate.hpp"

template<
	typename Environment
>
GLint
sge::opengl::glsl::programfuncs::link_status(
	typename Environment::program_context const &_context,
	typename Environment::handle const _handle
)
{
	return
		programfuncs::get_integer<
			Environment
		>(
			_context,
			_handle,
			_context.link_status_type()
		);
}

#define SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_LINK_STATUS(\
	env\
)\
template \
GLint \
sge::opengl::glsl::programfuncs::link_status<\
	env\
>(\
	env::program_context const &,\
	env::handle\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_LINK_STATUS
)
