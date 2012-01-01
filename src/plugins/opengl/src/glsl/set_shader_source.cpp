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


#include <sge/opengl/common.hpp>
#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/glsl/set_shader_source.hpp>
#include <sge/opengl/glsl/shader_contexts.hpp>
#include <sge/opengl/glsl/shaderfuncs/source.hpp>
#include <sge/renderer/glsl/string.hpp>


template<
	typename Environment
>
void
sge::opengl::glsl::set_shader_source(
	typename Environment::shader_context const &_context,
	typename Environment::handle const _id,
	renderer::glsl::string const &_source
)
{
	renderer::glsl::char_ const *const ptr(
		_source.c_str()
	);

	GLint const len(
		static_cast<
			GLint
		>(
			_source.size()
		)
	);

	shaderfuncs::source<
		Environment
	>(
		_context,
		_id,
		1,
		const_cast<
			typename Environment::char_ const **
		>(
			&ptr
		),
		&len
	);
}

#define SGE_OPENGL_GLSL_INSTANTIATE_SET_SHADER_SOURCE(\
	env\
)\
template \
void \
sge::opengl::glsl::set_shader_source<\
	env\
>(\
	env::shader_context const &,\
	env::handle, \
	sge::renderer::glsl::string const & \
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_SET_SHADER_SOURCE
)
