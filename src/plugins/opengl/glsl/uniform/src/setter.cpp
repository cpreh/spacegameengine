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
#include <sge/once.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <sge/format.hpp>
#include <sge/assert.hpp>

namespace
{

PFNGLUNIFORM1IVPROC uniform_1iv;
PFNGLUNIFORM2IVPROC uniform_2iv;
PFNGLUNIFORM3IVPROC uniform_3iv;
PFNGLUNIFORM4IVPROC uniform_4iv;
PFNGLUNIFORM1FVPROC uniform_1fv;
PFNGLUNIFORM2FVPROC uniform_2fv;
PFNGLUNIFORM3FVPROC uniform_3fv;
PFNGLUNIFORM3FVPROC uniform_4fv;
PFNGLUNIFORMMATRIX2FVPROC uniform_matrix_2fv;
PFNGLUNIFORMMATRIX3FVPROC uniform_matrix_3fv;
PFNGLUNIFORMMATRIX4FVPROC uniform_matrix_4fv;
PFNGLUNIFORMMATRIX2X3FVPROC uniform_matrix_2x3fv;
PFNGLUNIFORMMATRIX3X2FVPROC uniform_matrix_3x2fv;
PFNGLUNIFORMMATRIX2X4FVPROC uniform_matrix_2x4fv;
PFNGLUNIFORMMATRIX4X2FVPROC uniform_matrix_4x2fv;
PFNGLUNIFORMMATRIX3X4FVPROC uniform_matrix_3x4fv;
PFNGLUNIFORMMATRIX4X3FVPROC uniform_matrix_4x3fv;

void initialize_setter();

sge::opengl::glsl::uniform::type const
set_float(
	GLint location,
	GLfloat const *data,
	GLsizei size,
	GLsizei elements);

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

sge::opengl::glsl::uniform::setter::setter(
	GLint const location)
:
	location(location)
{
	initialize_setter();
}

sge::opengl::glsl::uniform::type const
sge::opengl::glsl::uniform::setter::operator()(
	renderer::glsl::uniform::int_value const &i) const
{
	return set_int(
		location,
		i.data(),
		element_size(
			i.type()
		),
		static_cast<GLsizei>(
			i.elements()
		)
	);
}

sge::opengl::glsl::uniform::type const
sge::opengl::glsl::uniform::setter::operator()(
	renderer::glsl::uniform::float_value const &f) const
{
	return is_matrix(f.type())
		? set_matrix(
			location,
			f.data(),
			element_columns(
				f.type()
			),
			element_rows(
				f.type()
			),
			static_cast<GLsizei>(
				f.elements()
			)
		)
		: set_float(
			location,
			f.data(),
			element_size(
				f.type()
			),
			static_cast<GLsizei>(
				f.elements()
			)
		);
}

namespace
{

void initialize_setter()
{
	SGE_FUNCTION_ONCE
	if(sge::opengl::glsl::is_native())
	{
		uniform_1iv = glUniform1iv;
		uniform_2iv = glUniform2iv;
		uniform_3iv = glUniform3iv;
		uniform_4iv = glUniform4iv;
		uniform_1fv = glUniform1fv;
		uniform_2fv = glUniform2fv;
		uniform_3fv = glUniform3fv;
		uniform_4fv = glUniform4fv;
		uniform_matrix_2fv = glUniformMatrix2fv;
		uniform_matrix_3fv = glUniformMatrix3fv;
		uniform_matrix_4fv = glUniformMatrix4fv;
		uniform_matrix_2x3fv = glUniformMatrix2x3fv;
		uniform_matrix_3x2fv = glUniformMatrix3x2fv;
		uniform_matrix_2x4fv = glUniformMatrix2x4fv;
		uniform_matrix_4x2fv = glUniformMatrix4x2fv;
		uniform_matrix_3x4fv = glUniformMatrix3x4fv;
		uniform_matrix_4x3fv = glUniformMatrix4x3fv;
	}
	else
	{
		uniform_1iv = glUniform1ivARB;
		uniform_2iv = glUniform2ivARB;
		uniform_3iv = glUniform3ivARB;
		uniform_4iv = glUniform4ivARB;
		uniform_1fv = glUniform1fvARB;
		uniform_2fv = glUniform2fvARB;
		uniform_3fv = glUniform3fvARB;
		uniform_4fv = glUniform4fvARB;
		uniform_matrix_2fv = glUniformMatrix2fvARB;
		uniform_matrix_3fv = glUniformMatrix3fvARB;
		uniform_matrix_4fv = glUniformMatrix4fvARB;
	}
}

sge::opengl::glsl::uniform::type const
set_float(
	GLint const location,
	GLfloat const *const data,
	GLsizei const size,
	GLsizei const elements)
{
	// FIXME: check errors!
	/*
	SGE_OPENGL_SENTRY(
		FCPPT_TEXT("uniform float failed"),
		sge::renderer::glsl::exception
	)
	*/

	namespace et = sge::opengl::glsl::uniform::element_type;

	switch(size) {
	case 1:
		uniform_1fv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::float1,
			elements);
	case 2:
		uniform_2fv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::float2,
			elements);
	case 3:
		uniform_3fv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::float3,
			elements);
	case 4:
		uniform_4fv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::float4,
			elements);
	default:
		throw sge::exception(
			(sge::format(
				FCPPT_TEXT("Invalid float dimension in glsl uniform: %1%"))
			% size).str());
	}
}

sge::opengl::glsl::uniform::type const
set_int(
	GLint const location,
	GLint const *const data,
	GLsizei const size,
	GLsizei const elements)
{
	// FIXME: check erroers
	/*
	SGE_OPENGL_SENTRY(
		FCPPT_TEXT("uniform int failed"),
		sge::renderer::glsl::exception
	)
	*/

	namespace et = sge::opengl::glsl::uniform::element_type;

	switch(size) {
	case 1:
		uniform_1iv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::int1,
			elements);
	case 2:
		uniform_2iv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::int2,
			elements);
	case 3:
		uniform_3iv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::int3,
			elements);
	case 4:
		uniform_4iv(
			location,
			elements,
			data);

		return sge::opengl::glsl::uniform::type(
			et::int4,
			elements);
	default:
		throw sge::exception(
			(sge::format(
				FCPPT_TEXT("Invalid vector dimension in glsl: %1%"))
			% size).str());
	}
}

sge::opengl::glsl::uniform::type const
set_matrix(
	GLint const location,
	GLfloat const *const data,
	GLsizei const rows,
	GLsizei const columns,
	GLsizei const elements)
{
	if(
		!sge::opengl::glsl::is_native()
		&& rows != columns
	)
		throw sge::exception(
			(sge::format(
				FCPPT_TEXT("You specified a glsl matrix whose dimensions are not equal which is not supported by the ARB extension!")
				FCPPT_TEXT(" Specified size was: %1%x%2%"))
			% columns
			% rows).str());

	namespace et = sge::opengl::glsl::uniform::element_type;

	// FIXME: check errors
	/*
	SGE_OPENGL_SENTRY(
		FCPPT_TEXT("uniform matrix failed"),
		sge::renderer::glsl::exception
	)
	*/

	switch(rows) {
	case 2:
		switch(columns) {
		case 2:
			uniform_matrix_2fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix2x2,
				elements);
		case 3:
			uniform_matrix_3x2fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix3x2,
				elements);
		case 4:
			uniform_matrix_4x2fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix4x2,
				elements);
		}
		break;
	case 3:
		switch(columns) {
		case 2:
			uniform_matrix_3x2fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix3x2,
				elements);
		case 3:
			uniform_matrix_3fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix3x3,
				elements);
		case 4:
			uniform_matrix_4x3fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix4x3,
				elements);
		}
		break;
	case 4:
		switch(columns) {
		case 2:
			uniform_matrix_4x2fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix4x2,
				elements);
		case 3:
			uniform_matrix_3x4fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix3x4,
				elements);
		case 4:
			uniform_matrix_4fv(
				location,
				elements,
				false,
				data);

			return sge::opengl::glsl::uniform::type(
				et::matrix4x4,
				elements);
		}
		break;
	}

	throw sge::exception(
		(sge::format(
			FCPPT_TEXT("Invalid matrix dimensions in glsl: %1%x%2%"))
			% columns
			% rows).str());
}

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
