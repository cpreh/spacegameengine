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
#include "../su.hpp"
#include "../export.hpp"
#include <boost/optional.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <cmath>

namespace sge
{
namespace math
{

/**
 * Calculates the angle between the two vectors using std::atan2
 */
template<typename Dest, typename T>
typename boost::enable_if<
	boost::is_floating_point<Dest>,
	boost::optional<Dest>
	>::type
angle_to(
	const basic_vector<T, 2>& from,
	const basic_vector<T, 2>& to)
{
	return atan2(structure_cast<Dest>(to - from));
}

/** 
 * Calculates the angle between the origin and the given vector using
 * sge::math::atan2.
 */
template<typename Dest, typename T>
typename boost::enable_if<
	boost::is_floating_point<Dest>,
	boost::optional<Dest>
	>::type
angle_to(
	const basic_vector<T, 2>& to)
{
	return atan2(structure_cast<Dest>(to));
}

/** 
 * Calculates an angle in the range \f$[-\pi,\pi]\f$ to an absolute angle in
 * \f$[0,2 \pi]\f$
 */
SGE_SYMBOL space_unit rel_angle_to_abs(space_unit);
/** 
 * Does the inverse of rel_angle_to_abs
 */
SGE_SYMBOL space_unit abs_angle_to_rel(space_unit);
SGE_SYMBOL bool is_rel_angle(space_unit);

}
}

#endif
