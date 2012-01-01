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


#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/glsl/uniform/element_type.hpp>
#include <sge/opengl/glsl/uniform/get.hpp>
#include <sge/opengl/glsl/uniform/location.hpp>
#include <sge/opengl/glsl/uniform/set.hpp>
#include <sge/opengl/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/uniform/value.hpp>
#include <fcppt/variant/object_impl.hpp>


template<
	typename Environment
>
sge::opengl::glsl::uniform::variable<Environment>::variable(
	uniform_context const &_context,
	handle const _program,
	renderer::glsl::string const &_name
)
:
	context_(
		_context
	),
	program_(
		_program
	),
	location_(
		uniform::location<
			Environment
		>(
			context_,
			_program,
			_name.c_str()
		)
	),
	stored_type_(
		element_type::nothing,
		0
	)
{
}

template<
	typename Environment
>
sge::opengl::glsl::uniform::variable<Environment>::~variable()
{
}

template<
	typename Environment
>
sge::renderer::glsl::uniform::value const
sge::opengl::glsl::uniform::variable<Environment>::get() const
{
	return
		uniform::get<
			Environment
		>(
			context_,
			program_,
			location_,
			stored_type_
		);
}

template<
	typename Environment
>
void
sge::opengl::glsl::uniform::variable<Environment>::set(
	renderer::glsl::uniform::value const &_value
)
{
	stored_type_ =
		uniform::set<
			Environment
		>(
			context_,
			location_,
			_value
		);
}

#define SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_VARIABLE(\
	env\
)\
template class \
sge::opengl::glsl::uniform::variable<\
	env\
>;

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_VARIABLE
)
