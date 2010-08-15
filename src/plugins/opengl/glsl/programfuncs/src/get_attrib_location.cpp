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


#include "../get_attrib_location.hpp"
#include "../../program_contexts.hpp"
#include "../../instantiate.hpp"
#include "../../../check_state.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

template<
	typename Environment
>
GLint
sge::opengl::glsl::programfuncs::get_attrib_location(
	typename Environment::program_context const &_context,
	typename Environment::handle const _handle,
	char const *const _name
)
{
	GLint const result(
		_context.get_attrib_location()(
			_handle,
			_name
		)
	);

	if(
		result == -1
	)
		throw sge::renderer::glsl::exception(
			FCPPT_TEXT("Get of the following attribute variable failed: \"")
			+ fcppt::from_std_string(
				_name
			)
			+ FCPPT_TEXT("\". This either means that the variable is not present in the shader, ")
			+ FCPPT_TEXT("or you tried to use a reserved name that starts with gl_. ")
			+ FCPPT_TEXT(" Please make sure your vertex declaration and vertex shader use the same names.")
		);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Getting attribute location \"")
		+ fcppt::from_std_string(
			_name
		)
		+ FCPPT_TEXT("\" failed."),
		sge::renderer::glsl::exception
	)

	return result;
}

#define SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_GET_ATTRIB_LOCATION(\
	env\
)\
template \
GLint \
sge::opengl::glsl::programfuncs::get_attrib_location<\
	env\
>(\
	env::program_context const &,\
	env::handle,\
	char const *\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_GET_ATTRIB_LOCATION
)
