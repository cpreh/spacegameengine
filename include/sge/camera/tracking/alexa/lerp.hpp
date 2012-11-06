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


#ifndef SGE_CAMERA_TRACKING_ALEXA_LERP_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_ALEXA_LERP_HPP_INCLUDED

#include <sge/camera/tracking/alexa/add.hpp>
#include <sge/camera/tracking/alexa/multiply.hpp>
#include <fcppt/math/matrix/object_fwd.hpp>

namespace sge
{
namespace camera
{
namespace tracking
{
namespace alexa
{
template
<
	typename T,
	typename DN,
	typename S
>
fcppt::math::matrix::object<T,DN,DN,S> const
lerp(
	T const t,
	fcppt::math::matrix::object<T,DN,DN,S> const &A,
	fcppt::math::matrix::object<T,DN,DN,S> const &B)
{
	return
		sge::camera::tracking::alexa::add(
			sge::camera::tracking::alexa::multiply(
				static_cast<T>(1)-t,
				A),
			sge::camera::tracking::alexa::multiply(
				t,
				B));
}
}
}
}
}

#endif
