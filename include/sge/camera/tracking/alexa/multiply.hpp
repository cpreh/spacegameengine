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


#ifndef SGE_CAMERA_TRACKING_ALEXA_MULTIPLY_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_ALEXA_MULTIPLY_HPP_INCLUDED

#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/exponential_pade.hpp>
#include <fcppt/math/matrix/logarithm.hpp>


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
multiply(
	T const _s,
	fcppt::math::matrix::object<T,DN,DN,S> const &_matrix)
{
	return
		fcppt::math::matrix::exponential_pade(
			_s *
			fcppt::math::matrix::logarithm(
				_matrix,
				static_cast<T>(
					1.0e-4),
				static_cast<T>(
					1.0e-9),
				static_cast<T>(
					1.0e-6)));
}
}
}
}
}

#endif
