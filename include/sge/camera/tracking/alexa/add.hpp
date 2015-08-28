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


#ifndef SGE_CAMERA_TRACKING_ALEXA_ADD_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_ALEXA_ADD_HPP_INCLUDED

#include <sge/camera/tracking/alexa/logarithm.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/exponential_pade.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/static.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{
namespace alexa
{

template<
	typename T,
	fcppt::math::size_type N,
	typename S1,
	typename S2
>
fcppt::math::matrix::static_<
	T,
	N,
	N
>
add(
	fcppt::math::matrix::object<
		T,
		N,
		N,
		S1
	> const &_a,
	fcppt::math::matrix::object<
		T,
		N,
		N,
		S2
	> const &_b
)
{
	return
		fcppt::math::matrix::exponential_pade(
			sge::camera::tracking::alexa::logarithm(
				_a
			)
			+
			sge::camera::tracking::alexa::logarithm(
				_b
			)
		);
}

}
}
}
}

#endif
