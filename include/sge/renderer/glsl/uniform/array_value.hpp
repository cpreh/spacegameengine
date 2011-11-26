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

#include <sge/renderer/size_type.hpp>
#include <sge/renderer/glsl/uniform/basic_value.hpp>
#include <sge/renderer/glsl/uniform/make_basic_value.hpp>
#include <sge/renderer/glsl/uniform/make_element_type.hpp>
#include <sge/renderer/glsl/uniform/variable.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
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
 * \brief Sets an array value for a uniform variable from a range
 *
 * Sets an array value of vectors or matrices for \a _var from the range from
 * \a _beg to \a _end.
 *
 * \tparam In An input iterator to fcppt::math::vector::static_ or
 * fcppt::math::matrix::static_
 *
 * \param _var The variable to set the value for
 *
 * \param _beg The beginning of the range
 *
 * \param _end One past the end of the range
*/
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

/**
 * \brief Sets an array value for a uniform variable from a container
 *
 * Sets an array value of vectors or matrices for \a _var from \a _cont.
 *
 * \tparam Container A container of fcppt::math::vector::static_ or
 * fcppt::math::matrix::static_
 *
 * \param _var The variable to set the value for
 *
 * \param _cont The container to store the data from
*/
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
