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


#include "../get_source.hpp"
#include "../../shader_contexts.hpp"
#include "../../instantiate.hpp"
#include "../../../check_state.hpp"
#include "../../../common.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

template<
	typename Environment
>
void
sge::opengl::glsl::shaderfuncs::get_source(
	typename Environment::shader_context const &_context,
	typename Environment::handle const _id,
	GLsizei const _buf_size,
	GLsizei *const _length,
	typename Environment::char_ *const _source
)
{
	_context.get_shader_source()(
		_id,
		_buf_size,
		_length,
		_source
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Getting a shader source failed"),
		sge::renderer::glsl::exception
	)
}

#define SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_GET_SOURCE(\
	env\
)\
template \
void \
sge::opengl::glsl::shaderfuncs::get_source<\
	env\
>(\
	env::shader_context const &,\
	env::handle, \
	GLsizei, \
	GLsizei *, \
	env::char_ * \
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_SHADERFUNCS_INSTANTIATE_GET_SOURCE
)
