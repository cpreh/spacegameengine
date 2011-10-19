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


#include "../get_shader_source.hpp"
#include "../instantiate.hpp"
#include "../shader_contexts.hpp"
#include "../shaderfuncs/get_integer.hpp"
#include "../shaderfuncs/get_source.hpp"
#include "../../common.hpp"
#include <sge/renderer/glsl/char.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/raw_vector_impl.hpp>

template<
	typename Environment
>
sge::renderer::glsl::string const
sge::opengl::glsl::get_shader_source(
	typename Environment::shader_context const &_context,
	typename Environment::handle const _id
)
{
	GLint const length(
		shaderfuncs::get_integer<
			Environment
		>(
			_context,
			_id,
			_context.source_length_type()
		)
	);

	// length includes the termination 0 character
	FCPPT_ASSERT_ERROR(
		length > 0
	);

	typedef fcppt::container::raw_vector<
		renderer::glsl::char_
	> raw_vector;

	raw_vector buffer(
		static_cast<
			typename raw_vector::size_type
		>(
			length
		)
	);

	shaderfuncs::get_source<
		Environment
	>(
		_context,
		_id,
		static_cast<
			GLsizei
		>(
			length
		),
		0, // length return
		buffer.data()
	);

	return
		renderer::glsl::string(
			buffer.begin(),
			buffer.end()
		);
}

#define SGE_OPENGL_GLSL_INSTANTIATE_GET_SHADER_SOURCE(\
	env\
)\
template \
sge::renderer::glsl::string const \
sge::opengl::glsl::get_shader_source<\
	env\
>(\
	env::shader_context const &,\
	env::handle \
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_GET_SHADER_SOURCE
)
