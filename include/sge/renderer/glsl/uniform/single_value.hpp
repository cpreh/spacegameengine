/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/glsl/uniform/make_element_type.hpp>
#include <sge/renderer/glsl/uniform/make_basic_value.hpp>
#include <sge/renderer/glsl/uniform/basic_value.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_fundamental.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

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
	variable_ptr const var,
	Value const &arg
)
{
	typedef typename make_basic_value<
		typename Value::value_type
	>::type value;

	typedef typename value::data_type data_type;

	var->set(
		value(
			data_type(
				arg.begin(),
				arg.end()
			),
			1u,
			make_element_type<
				Value
			>::value
		)
	);
		
}

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
	variable_ptr const var,
	Value const &arg
)
{
	single_value(
		var,
		typename fcppt::math::vector::static_<
			Value,
			1
		>::type(
			arg
		)
	);
}

}
}
}
}

#endif
