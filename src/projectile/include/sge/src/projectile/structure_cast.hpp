/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_PROJECTILE_STRUCTURE_CAST_HPP_INCLUDED
#define SGE_SRC_PROJECTILE_STRUCTURE_CAST_HPP_INCLUDED

//#include <fcppt/math/matrix/has_dim.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/has_dim.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


// TODO: We don't need most of this

namespace sge
{
namespace projectile
{

template<
	typename Container
>
typename
boost::enable_if<
	fcppt::math::vector::has_dim<
		Container,
		3u
	>,
	Container
>::type
structure_cast(
	btVector3 const &_s
)
{
	return
		Container(
			static_cast<typename Container::value_type>(
				_s[0]),
			static_cast<typename Container::value_type>(
				_s[1]),
			static_cast<typename Container::value_type>(
				_s[2]));
}

template<
	typename T,
	typename S
>
btVector3
structure_cast(
	fcppt::math::vector::object<
		T,
		3,
		S
	> const &_c
)
{
	return
		btVector3(
			static_cast<btScalar>(_c[0]),
			static_cast<btScalar>(_c[1]),
			static_cast<btScalar>(_c[2]));
}

/*
template<
	typename Container
>
typename
boost::enable_if<
	fcppt::math::matrix::has_dim<
		Container,
		3u,
		3u
	>,
	Container
>::type
structure_cast(
	btMatrix3x3 const &_matrix
)
{
	return
		Container(
			m[0].getX(),m[0].getY(),m[0].getZ(),
			m[1].getX(),m[1].getY(),m[1].getZ(),
			m[2].getX(),m[2].getY(),m[2].getZ()
		);
}*/

template<
	typename T,
	typename S
>
btMatrix3x3
structure_cast(
	fcppt::math::matrix::object<
		T,
		3,
		3,
		S
	> const _m
)
{
	return
		btMatrix3x3(
			_m[0][0],_m[0][1],_m[0][2],
			_m[1][0],_m[1][1],_m[1][2],
			_m[2][0],_m[2][1],_m[2][2]
		);
}

}
}

#endif
