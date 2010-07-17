/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../setter.hpp"
#include "../../init.hpp"
#include <sge/renderer/glsl/uniform/int_value_type.hpp>
#include <sge/renderer/glsl/uniform/float_value_type.hpp>
#include <sge/renderer/glsl/exception.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/format.hpp>
#include <fcppt/assert.hpp>

namespace
{

sge::opengl::glsl::uniform::type const
set_int(
	GLint location,
	GLint const *data,
	GLsizei size,
	GLsizei elements);

sge::opengl::glsl::uniform::type const
set_matrix(
	GLint location,
	GLfloat const *data,
	GLsizei rows,
	GLsizei columns,
	GLsizei elements);

bool
is_matrix(
	sge::renderer::glsl::uniform::float_value_type::type);

GLsizei
element_size(
	sge::renderer::glsl::uniform::int_value_type::type);

GLsizei
element_size(
	sge::renderer::glsl::uniform::float_value_type::type);

GLsizei
element_columns(
	sge::renderer::glsl::uniform::float_value_type::type);

GLsizei
element_rows(
	sge::renderer::glsl::uniform::float_value_type::type);

}

template<
	typename Environment
>
sge::opengl::glsl::uniform::set_visitor<Environment>::set_visitor(
	uniform_context const &_context,
	GLint const _location
)
:
	context_(
		_context
	),
	location_(
		_location
	)
{}

template<
	typename Environment
>
sge::opengl::glsl::uniform::type const
sge::opengl::glsl::uniform::set_visitor<Environment>::operator()(
	renderer::glsl::uniform::int_value const &_value
) const
{
	return
		set_int<
			Environment
		>(
			context_,
			location_,
			_value.data(),
			element_size(
				_value.type()
			),
			static_cast<
				GLsizei
			>(
				_value.elements()
			)
		);
}

template<
	typename Environment
>
sge::opengl::glsl::uniform::type const
sge::opengl::glsl::uniform::set_visitor<Environment>::operator()(
	renderer::glsl::uniform::float_value const &_value
) const
{
	return
		is_matrix(
			_value.type()
		)
		?
			set_matrix<
				Environment
			>(
				context_,
				location_,
				_value.data(),
				element_columns(
					_value.type()
				),
				element_rows(
					_value.type()
				),
				static_cast<
					GLsizei
				>(
					_value.elements()
				)
			)
		:
			set_float<
				Environment
			>(
				context_,
				location_,
				_value.data(),
				element_size(
					_value.type()
				),
				static_cast<
					GLsizei
				>(
					_value.elements()
				)
			);
}

namespace
{

// TODO: add some assertions!

bool
is_matrix(
	sge::renderer::glsl::uniform::float_value_type::type const type)
{
	return type >= sge::renderer::glsl::uniform::float_value_type::matrix2x2;
}

GLsizei
element_size(
	sge::renderer::glsl::uniform::int_value_type::type const t)
{
	return static_cast<GLsizei>(t) + 1;
}

GLsizei
element_size(
	sge::renderer::glsl::uniform::float_value_type::type const t)
{
	return static_cast<GLsizei>(t) + 1;
}

GLsizei
element_columns(
	sge::renderer::glsl::uniform::float_value_type::type const t)
{
	namespace fv = sge::renderer::glsl::uniform::float_value_type;

	switch(t) {
	case fv::matrix2x2:
	case fv::matrix2x3:
	case fv::matrix2x4:
		return 2;
	case fv::matrix3x2:
	case fv::matrix3x3:
	case fv::matrix3x4:
		return 3;
	case fv::matrix4x2:
	case fv::matrix4x3:
	case fv::matrix4x4:
		return 4;
	default:
		throw sge::exception(
			FCPPT_TEXT("Invalid matrix type in glsl element_columns!"));
	}
}

GLsizei
element_rows(
	sge::renderer::glsl::uniform::float_value_type::type const t)
{
	namespace fv = sge::renderer::glsl::uniform::float_value_type;

	switch(t) {
	case fv::matrix2x2:
	case fv::matrix3x2:
	case fv::matrix4x2:
		return 2;
	case fv::matrix2x3:
	case fv::matrix3x3:
	case fv::matrix4x3:
		return 3;
	case fv::matrix2x4:
	case fv::matrix3x4:
	case fv::matrix4x4:
		return 4;
	default:
		throw sge::exception(
			FCPPT_TEXT("Invalid matrix type in glsl element_rows!"));
	}
}

}
