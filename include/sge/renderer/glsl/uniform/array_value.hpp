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


#ifndef SGE_RENDERER_GLSL_UNIFORM_ARRAY_VALUE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_ARRAY_VALUE_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/make_basic_value.hpp>
#include <sge/renderer/glsl/uniform/make_element_type.hpp>
#include <sge/renderer/glsl/uniform/basic_value.hpp>
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
	uniform::variable &_var,
	In const _beg,
	In const _end
)
{
	typedef typename std::iterator_traits<
		In
	>::value_type it_value_type;

	typedef typename uniform::make_basic_value<
		typename it_value_type::value_type
	>::type value_type;

	typedef typename value_type::data_type data_type;

	data_type buffer;

	size_type count = 0;

	for(
		In it(_beg);
		it != _end;
		++it, ++count
	)
		buffer.insert(
			buffer.end(),
			it->begin(),
			it->end()
		);

	_var.set(
		value_type(
			buffer,
			count,
			uniform::make_element_type<
				it_value_type
			>::value
		)
	);
}

template<
	typename Container
>
void
array_value(
	uniform::variable &_var,
	Container const &_cont
)
{
	uniform::array_value(
		_var,
		_cont.begin(),
		_cont.end()
	);
}

}
}
}
}

#endif
