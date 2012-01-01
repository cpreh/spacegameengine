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


#ifndef SGE_OPENGL_RANGE_CHECK_HPP_INCLUDED
#define SGE_OPENGL_RANGE_CHECK_HPP_INCLUDED

#include <fcppt/math/size_type.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{

template<
	typename T,
	typename M,
	typename S,
	fcppt::math::size_type N
>
typename boost::enable_if_c<
	N == M::value,
	bool
>::type
range_check(
	fcppt::math::dim::basic<
		T,
		M,
		S
	> const &_dim,
	fcppt::math::box::basic<
		T,
		N
	> const &_box
)
{
	for(
		typename fcppt::math::box::basic<
			T,
			N
		>::size_type index = 0;
		index < N;
		++index
	)
		if(
			_box.max()[index]
			> _dim[index]
		)
			return false;
	return true;
}

}
}

#endif
