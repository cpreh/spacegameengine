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


#include "../set_visitor.hpp"
#include "../set_int.hpp"
#include "../set_float.hpp"
#include "../set_matrix.hpp"
#include "../is_matrix.hpp"
#include "../element_size_int.hpp"
#include "../element_size_float.hpp"
#include "../element_columns.hpp"
#include "../element_rows.hpp"
#include "../../instantiate.hpp"

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
		uniform::set_int<
			Environment
		>(
			context_,
			location_,
			_value.data(),
			uniform::element_size_int(
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
		uniform::is_matrix(
			_value.type()
		)
		?
			uniform::set_matrix<
				Environment
			>(
				context_,
				location_,
				_value.data(),
				uniform::element_columns(
					_value.type()
				),
				uniform::element_rows(
					_value.type()
				),
				static_cast<
					GLsizei
				>(
					_value.elements()
				)
			)
		:
			uniform::set_float<
				Environment
			>(
				context_,
				location_,
				_value.data(),
				uniform::element_size_float(
					_value.type()
				),
				static_cast<
					GLsizei
				>(
					_value.elements()
				)
			);
}

#define SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_SET_VISITOR(\
	env\
)\
template class \
sge::opengl::glsl::uniform::set_visitor<\
	env\
>;

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_UNIFORM_INSTANTIATE_SET_VISITOR
)
