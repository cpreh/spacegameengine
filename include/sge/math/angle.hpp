/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MATH_ANGLE_HPP_INCLUDED
#define SGE_MATH_ANGLE_HPP_INCLUDED

#include "atan2.hpp"
#include "vector.hpp"
#include "mod.hpp"
#include "constants.hpp"
#include "../exception.hpp"
#include "../text.hpp"
#include "../format.hpp"
#include <boost/optional.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cmath>

namespace sge
{
namespace math
{

template<typename Dest, typename T>
typename boost::enable_if<
	boost::is_floating_point<Dest>,
	boost::optional<Dest>
	>::type
angle_to(
	const vector<T, 2>& from,
	const vector<T, 2>& to)
{
	return atan2(structure_cast<Dest>(to - from));
}

template<typename Dest, typename T>
typename boost::enable_if<
	boost::is_floating_point<Dest>,
	boost::optional<Dest>
	>::type
angle_to(
	const vector<T, 2>& to)
{
	return atan2(structure_cast<Dest>(to));
}

template<
	typename T
>
T rel_angle_to_abs(
	T const a)
{
	if(!is_rel_angle(a))
		throw exception(
			(format(SGE_TEXT("math::rel_angle_to_abs: relative angle %1% out of range!"))
			% a).str());

	if (almost_zero(a))
		return su(0);

	return a > su(0) ? a : twopi<T>()+a;
}

template<
	typename T
>
T abs_angle_to_rel(
	T a)
{
	a = mod(a, twopi<T>());

	if (is_rel_angle(a))
		return a;
	
	return a > 0 
		? a - twopi<T>() 
		: a + twopi<T>();
}

template<
	typename T
>
bool is_rel_angle(
	T const a)
{
	return in_closed_interval(
		a,
		-pi<T>(),
		pi<T>());
}

}
}

#endif
