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

#ifndef SGE_MATH_COMPARE_HPP_INCLUDED
#define SGE_MATH_COMPARE_HPP_INCLUDED

#include <sge/math/diff.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <limits>

namespace sge
{
namespace math
{
/**
 * Uses std::numeric_limits<T>::epsilon to check if \c a is nearly equal to \c b.
 */
template<typename T>
inline bool nearly_equals(const T& a, const T& b)
{
	return diff(a, b) < std::numeric_limits<T>::epsilon();
}

/**
 * This is the non floating point version of compare which simply uses operator==
 */
template<typename T>
inline typename boost::disable_if<boost::is_floating_point<T>, bool>::type compare(const T& a, const T& b)
{
	return a == b;
}

/**
 * The floating point version of compare uses sge::math::nearly_equals
 */
template<typename T>
inline typename boost::enable_if<boost::is_floating_point<T>, bool>::type compare(const T& a, const T& b)
{
	return nearly_equals(a, b);
}

/**
 * Applies sge::math::compare to \c t and 0
 */
template<typename T>
inline bool almost_zero(const T t)
{
	return compare(t, static_cast<T>(0));
}

/**
 * Checks if \c t is in \f$[l,r]\f$
 */
template<typename T>
inline bool in_closed_interval(const T &t,const T &l,const T &r)
{
	return t >= l && t <= r;
}
}
}

#endif
