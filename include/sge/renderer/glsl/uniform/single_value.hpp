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


#ifndef SGE_RENDERER_GLSL_UNIFORM_SINGLE_VALUE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_SINGLE_VALUE_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/basic_value.hpp>
#include <sge/renderer/glsl/uniform/make_basic_value.hpp>
#include <sge/renderer/glsl/uniform/make_element_type.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

/**
\brief Sets a single vector/matrix value for a uniform variable

Sets a single value of a vector or a matrix for \a _var from \a _arg.

\param _var The variable to set the value for

\param _arg The value to set

\see uniform::make_element_type
*/
template<
	typename Value
>
typename boost::disable_if<
	boost::is_fundamental<
		Value
	>,
	void
>::type
single_value(
	uniform::variable &_var,
	Value const &_arg
)
{
	typedef typename uniform::make_basic_value<
		typename Value::value_type
	>::type cur_value;

	typedef typename cur_value::data_type data_type;

	_var.set(
		cur_value(
			data_type(
				_arg.begin(),
				_arg.end()
			),
			1u,
			uniform::make_element_type<
				Value
			>::value
		)
	);

}

/**
\brief Sets a single fundamental value for a uniform variable

Sets a single value of a fundamental type for \a _var from \a _arg.

\param _var The variable to set the value for

\param _arg The value to set
*/
template<
	typename Value
>
typename boost::enable_if<
	boost::is_fundamental<
		Value
	>,
	void
>::type
single_value(
	uniform::variable &_var,
	Value const &_arg
)
{
	uniform::single_value(
		_var,
		typename fcppt::math::vector::static_<
			Value,
			1
		>::type(
			_arg
		)
	);
}

}
}
}
}

#endif
