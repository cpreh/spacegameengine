/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/glsl/uniform/contexts.hpp>
#include <sge/opengl/glsl/uniform/location.hpp>
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>


template<
	typename Environment
>
GLint
sge::opengl::glsl::uniform::location(
	typename Environment::uniform_context const &_context,
	typename Environment::handle const _program,
	char const *const _name
)
{
	GLint const ret(
		_context.get_uniform_location()(
			_program,
			_name
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGetUniformLocation failed"),
		sge::renderer::glsl::exception
	)

	return ret;
}

#define SGE_OPENGL_GLSL_INSTANTIATE_UNIFORM_LOCATION(\
	env\
)\
template \
GLint \
sge::opengl::glsl::uniform::location<\
	env\
>(\
	env::uniform_context const &,\
	env::handle,\
	char const *\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_UNIFORM_LOCATION
)
