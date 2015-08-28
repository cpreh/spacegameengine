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


#ifndef SGE_CAMERA_TRACKING_ALEXA_LOGARITHM_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_ALEXA_LOGARITHM_HPP_INCLUDED

#include <fcppt/literal.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/logarithm.hpp>
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
	typename S
>
fcppt::math::matrix::static_<
	T,
	N,
	N
>
logarithm(
	fcppt::math::matrix::object<
		T,
		N,
		N,
		S
	> const &_matrix
)
{
	return
		fcppt::math::matrix::logarithm(
			_matrix,
			fcppt::literal<
				T
			>(
				1.0e-4
			),
			fcppt::literal<
				T
			>(
				1.0e-9
			),
			fcppt::literal<
				T
			>(
				1.0e-6
			)
		);
}

}
}
}
}

#endif
