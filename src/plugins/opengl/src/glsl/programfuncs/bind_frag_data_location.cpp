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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/glsl/program_contexts.hpp>
#include <sge/opengl/glsl/programfuncs/bind_frag_data_location.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>


template<
	typename Environment
>
void
sge::opengl::glsl::programfuncs::bind_frag_data_location(
	typename Environment::program_context const &_context,
	typename Environment::handle const _program,
	GLuint const _index,
	char const *const _name
)
{
	typename Environment::program_context::gl_bind_frag_data_location const function(
		_context.bind_frag_data_location()
	);

	if(
		!function
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("glBindFragDataLocation"),
			FCPPT_TEXT("3.0"),
			FCPPT_TEXT("")
		);

	function(
		_program,
		_index,
		_name
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Binding a frag data location failed!"),
		sge::renderer::glsl::exception
	)
}

#define SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_BIND_FRAG_DATA_LOCATION(\
	env\
)\
template \
void \
sge::opengl::glsl::programfuncs::bind_frag_data_location<\
	env\
>(\
	env::program_context const &,\
	env::handle,\
	GLuint,\
	char const *\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_PROGRAMFUNCS_INSTANTIATE_BIND_FRAG_DATA_LOCATION
)
