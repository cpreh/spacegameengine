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


#ifndef SGE_SRC_PROJECTILE_STRUCTURE_CAST_HPP_INCLUDED
#define SGE_SRC_PROJECTILE_STRUCTURE_CAST_HPP_INCLUDED

#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/has_dim.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/has_dim.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/has_dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::vector::has_dim<Container,static_cast<fcppt::math::size_type>(3)>::value ||
	fcppt::math::dim::has_dim<Container,static_cast<fcppt::math::size_type>(3)>::value,
	Container
>::type
structure_cast(
	btVector3 const &s)
{
	return
		Container(
			static_cast<typename Container::value_type>(
				s[0]),
			static_cast<typename Container::value_type>(
				s[1]),
			static_cast<typename Container::value_type>(
				s[2]));
}

template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::vector::has_dim<Container,static_cast<fcppt::math::size_type>(3)>::value ||
	fcppt::math::dim::has_dim<Container,static_cast<fcppt::math::size_type>(3)>::value,
	btVector3
>::type
structure_cast(
	Container const &c)
{
	return
		btVector3(
			static_cast<btScalar>(c[0]),
			static_cast<btScalar>(c[1]),
			static_cast<btScalar>(c[2]));
}





template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::matrix::has_dim<Container,static_cast<fcppt::math::size_type>(3),static_cast<fcppt::math::size_type>(3)>::value,
	Container
>::type
structure_cast(
	btMatrix3x3 const &m)
{
	return
		Container(
			m[0].getX(),m[0].getY(),m[0].getZ(),
			m[1].getX(),m[1].getY(),m[1].getZ(),
			m[2].getX(),m[2].getY(),m[2].getZ());
}

template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::matrix::has_dim<Container,static_cast<fcppt::math::size_type>(3),static_cast<fcppt::math::size_type>(3)>::value,
	btMatrix3x3
>::type
structure_cast(
	Container const &m)
{
	return
		btMatrix3x3(
			m[0][0],m[0][1],m[0][2],
			m[1][0],m[1][1],m[1][2],
			m[2][0],m[2][1],m[2][2]);
}
}
}

#endif
