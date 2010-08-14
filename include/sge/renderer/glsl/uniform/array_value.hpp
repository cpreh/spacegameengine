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


#ifndef SGE_RENDERER_GLSL_UNIFORM_ARRAY_VALUE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_ARRAY_VALUE_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/make_basic_value.hpp>
#include <sge/renderer/glsl/uniform/make_element_type.hpp>
#include <sge/renderer/glsl/uniform/basic_value.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <iterator>

namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

template<
	typename In
>
void
array_value(
	variable_ptr const var,
	In const beg,
	In const end
)
{
	typedef typename std::iterator_traits<
		In
	>::value_type value_type;

	typedef typename make_basic_value<
		typename value_type::value_type
	>::type value;

	typedef typename value::data_type data_type;

	data_type buffer;

	size_type count = 0;

	for(
		In it(beg);
		it != end;
		++it, ++count
	)
		buffer.insert(
			buffer.end(),
			it->begin(),
			it->end()
		);

	var->set(
		value(
			buffer,
			count,
			make_element_type<
				value_type
			>::value
		)
	);
}

template<
	typename Container
>
void
array_value(
	variable_ptr const var,
	Container const &cont
)
{
	array_value(
		var,
		cont.begin(),
		cont.end()
	);
}

}
}
}
}

#endif
