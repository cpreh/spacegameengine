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


#include <sge/opengl/glsl/uniform/set_int.hpp>
#include <sge/opengl/glsl/uniform/contexts.hpp>
#include <sge/opengl/glsl/uniform/type.hpp>
#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>


namespace
{

template<
	typename Environment
>
sge::opengl::glsl::uniform::type const
set_int_impl(
	typename Environment::uniform_context const &_context,
	GLint const _location,
	GLint const *const _data,
	GLsizei const _size,
	GLsizei const _elements
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;

	switch(
		_size
	)
	{
	case 1:
		_context.uniform_1iv()(
			_location,
			_elements,
			_data
		);

		return
			sge::opengl::glsl::uniform::type(
				et::int1,
				_elements
			);
	case 2:
		_context.uniform_2iv()(
			_location,
			_elements,
			_data
		);

		return
			sge::opengl::glsl::uniform::type(
				et::int2,
				_elements
			);
	case 3:
		_context.uniform_3iv()(
			_location,
			_elements,
			_data
		);

		return
			sge::opengl::glsl::uniform::type(
				et::int3,
				_elements
			);
	case 4:
		_context.uniform_4iv()(
			_location,
			_elements,
			_data
		);

		return
			sge::opengl::glsl::uniform::type(
				et::int4,
				_elements
			);
	}

	throw sge::renderer::glsl::exception(
		(
			fcppt::format(
				FCPPT_TEXT("Invalid vector dimension in glsl: %1%")
			)
			% _size
		).str()
	);
}

}

template<
	typename Environment
>
sge::opengl::glsl::uniform::type const
sge::opengl::glsl::uniform::set_int(
	typename Environment::uniform_context const &_context,
	GLint const _location,
	GLint const *const _data,
	GLsizei const _size,
	GLsizei const _elements
)
{
	sge::opengl::glsl::uniform::type const ret(
		set_int_impl<
			Environment
		>(
			_context,
			_location,
			_data,
			_size,
			_elements
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("uniform int failed"),
		sge::renderer::glsl::exception
	)

	return ret;

}

#define SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_SET_INT(\
	env\
)\
template \
sge::opengl::glsl::uniform::type const \
sge::opengl::glsl::uniform::set_int<\
	env\
>(\
	env::uniform_context const &,\
	GLint,\
	GLint const *,\
	GLsizei,\
	GLsizei\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_SET_INT
)
