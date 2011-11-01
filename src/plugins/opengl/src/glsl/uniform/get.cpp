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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/glsl/instantiate.hpp>
#include <sge/opengl/glsl/uniform/contexts.hpp>
#include <sge/opengl/glsl/uniform/convert_type.hpp>
#include <sge/opengl/glsl/uniform/element_count.hpp>
#include <sge/opengl/glsl/uniform/get.hpp>
#include <sge/opengl/glsl/uniform/type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/glsl/exception.hpp>
#include <sge/renderer/glsl/uniform/float_value.hpp>
#include <sge/renderer/glsl/uniform/int_value.hpp>
#include <sge/renderer/glsl/uniform/value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{

template<
	typename Environment,
	typename ValueType,
	typename Function
>
sge::renderer::glsl::uniform::value const
get_impl(
	typename Environment::handle const _program,
	GLint const _location,
	sge::opengl::glsl::uniform::type const &_type,
	Function const &_function
)
{
	typedef typename ValueType::element_type element_type;

	sge::opengl::glsl::uniform::size_type const elements(
		sge::opengl::glsl::uniform::element_count(
			_type.element_type()
		)
	);

	typename ValueType::data_type data(
		static_cast<
			typename ValueType::data_type::size_type
		>(
			elements * _type.elements()
		)
	);

	for(
		sge::opengl::glsl::uniform::size_type i = 0;
		i < _type.elements();
		++i
	)
	{
		_function(
			_program,
			_location,
			data.data() + i * elements
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("Getting a uniform variable failed"),
			sge::renderer::glsl::exception
		)
	}

	return
		sge::renderer::glsl::uniform::value(
			ValueType(
				data,
				static_cast<
					sge::renderer::size_type
				>(
					elements
				),
				sge::opengl::glsl::uniform::convert_type<
					element_type
				>(
					_type.element_type()
				)
			)
		);
}

}

template<
	typename Environment
>
sge::renderer::glsl::uniform::value const
sge::opengl::glsl::uniform::get(
	typename Environment::uniform_context const &_context,
	typename Environment::handle const _program,
	GLint const _location,
	type const &_type
)
{
	switch(
		_type.element_type()
	)
	{
	case element_type::int1:
	case element_type::int2:
	case element_type::int3:
	case element_type::int4:
		return
			::get_impl<
				Environment,
				renderer::glsl::uniform::int_value
			>(
				_program,
				_location,
				_type,
				_context.get_uniform_iv()
			);
	case element_type::float1:
	case element_type::float2:
	case element_type::float3:
	case element_type::float4:
	case element_type::matrix2x2:
	case element_type::matrix3x3:
	case element_type::matrix4x4:
	case element_type::matrix2x3:
	case element_type::matrix3x2:
	case element_type::matrix2x4:
	case element_type::matrix4x2:
	case element_type::matrix3x4:
	case element_type::matrix4x3:
		return
			::get_impl<
				Environment,
				renderer::glsl::uniform::float_value
			>(
				_program,
				_location,
				_type,
				_context.get_uniform_fv()
			);
	case element_type::nothing:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

#define SGE_OPENGL_GLSL_INSTANTIATE_UNIFORM_GET(\
	env\
)\
template sge::renderer::glsl::uniform::value const \
sge::opengl::glsl::uniform::get<\
	env\
>(\
	env::uniform_context const &,\
	env::handle,\
	GLint,\
	sge::opengl::glsl::uniform::type const &\
);

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_UNIFORM_GET
)
