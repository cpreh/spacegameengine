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
#include <sge/opengl/glsl/make_shader_type.hpp>
#include <sge/opengl/glsl/shader_contexts.hpp>
#include <fcppt/assert/unreachable.hpp>


template<
	typename Environment
>
GLenum
sge::opengl::glsl::make_shader_type(
	typename Environment::shader_context const &_context,
	shader_type::type const _type
)
{
	switch(
		_type
	)
	{
	case shader_type::vertex:
		return
			_context.vertex_shader_type();
	case shader_type::pixel:
		return
			_context.pixel_shader_type();
	case shader_type::geometry:
		return
			_context.geometry_shader_type();
	case shader_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

#define SGE_OPENGL_GLSL_INSTANTIATE_MAKE_SHADER_TYPE(\
	env\
)\
template \
GLenum \
sge::opengl::glsl::make_shader_type<\
	env\
>(\
	env::shader_context const &,\
	shader_type::type\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_MAKE_SHADER_TYPE
)
