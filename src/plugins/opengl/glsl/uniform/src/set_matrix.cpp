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


#include "../set_matrix.hpp"
#include "../element_type.hpp"
#include "../contexts.hpp"
#include "../type.hpp"
#include "../../instantiate.hpp"
#include "../../../check_state.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

namespace
{

bool const transpose = true;

sge::opengl::glsl::uniform::type const
set_matrix_impl(
	sge::opengl::glsl::native::uniform_context const &_context,
	GLint const _location,
	GLfloat const *const _data,
	GLsizei const _columns,
	GLsizei const _rows,
	GLsizei const _elements
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;

	switch(
		_rows
	)
	{
	case 2:
		switch(
			_columns
		)
		{
		case 2:
			_context.uniform_matrix_2fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix2x2,
					_elements
				);
		case 3:
			_context.uniform_matrix_3x2fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix3x2,
					_elements
				);
		case 4:
			_context.uniform_matrix_4x2fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix4x2,
					_elements
				);
		}
		break;
	case 3:
		switch(
			_columns
		)
		{
		case 2:
			_context.uniform_matrix_3x2fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix3x2,
					_elements
				);
		case 3:
			_context.uniform_matrix_3fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix3x3,
					_elements
				);
		case 4:
			_context.uniform_matrix_4x3fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix4x3,
					_elements
				);
		}
		break;
	case 4:
		switch(
			_columns
		)
		{
		case 2:
			_context.uniform_matrix_4x2fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix4x2,
					_elements
				);
		case 3:
			_context.uniform_matrix_3x4fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix3x4,
					_elements
				);
		case 4:
			_context.uniform_matrix_4fv()(
				_location,
				_elements,
				transpose,
				_data
			);

			return
				sge::opengl::glsl::uniform::type(
					et::matrix4x4,
					_elements
				);
		}
		break;
	}

	throw sge::renderer::glsl::exception(
		(
			fcppt::format(
				FCPPT_TEXT("Invalid matrix dimensions in glsl: %1%x%2%")
			)
			% _columns
			% _rows
		).str()
	);
}

sge::opengl::glsl::uniform::type const
set_matrix_impl(
	sge::opengl::glsl::arb::uniform_context const &_context,
	GLint const _location,
	GLfloat const *const _data,
	GLsizei const _columns,
	GLsizei const _rows,
	GLsizei const _elements
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;

	if(
		_rows != _columns
	)
		throw sge::renderer::glsl::exception(
			(
				fcppt::format(
					FCPPT_TEXT("You specified a glsl matrix whose dimensions are not equal which is not supported by the ARB extension!")
					FCPPT_TEXT(" Specified size was: %1%x%2%")
				)
				% _columns
				% _rows
			).str()
		);

	switch(
		_rows
	)
	{
	case 2:
		_context.uniform_matrix_2fv()(
			_location,
			_elements,
			transpose,
			_data
		);

		return
			sge::opengl::glsl::uniform::type(
				et::matrix2x2,
				_elements
			);

	case 3:
		_context.uniform_matrix_3fv()(
			_location,
			_elements,
			transpose,
			_data
		);

		return
			sge::opengl::glsl::uniform::type(
				et::matrix3x3,
				_elements
			);
	case 4:
		_context.uniform_matrix_4fv()(
			_location,
			_elements,
			transpose,
			_data
		);

		return
			sge::opengl::glsl::uniform::type(
				et::matrix4x4,
				_elements
			);
	}

	throw sge::renderer::glsl::exception(
		(
			fcppt::format(
				FCPPT_TEXT("Invalid matrix dimensions in glsl: %1%x%2%")
			)
			% _columns
			% _rows
		).str()
	);
}

}

template<
	typename Environment
>
sge::opengl::glsl::uniform::type const
sge::opengl::glsl::uniform::set_matrix(
	typename Environment::uniform_context const &_context,
	GLint const _location,
	GLfloat const *const _data,
	GLsizei const _columns,
	GLsizei const _rows,
	GLsizei const _elements
)
{
	sge::opengl::glsl::uniform::type const ret(
		set_matrix_impl(
			_context,
			_location,
			_data,
			_columns,
			_rows,
			_elements
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("uniform float failed"),
		sge::renderer::glsl::exception
	)

	return ret;
}

#define SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_SET_MATRIX(\
	env\
)\
template \
sge::opengl::glsl::uniform::type const \
sge::opengl::glsl::uniform::set_matrix<\
	env\
>(\
	env::uniform_context const &,\
	GLint,\
	GLfloat const *,\
	GLsizei,\
	GLsizei,\
	GLsizei\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_SET_MATRIX
)
