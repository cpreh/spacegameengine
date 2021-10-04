//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_TRACKING_ALEXA_MULTIPLY_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_ALEXA_MULTIPLY_HPP_INCLUDED

#include <sge/camera/tracking/alexa/logarithm.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/exponential_pade.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/static.hpp>


namespace sge::camera::tracking::alexa
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
multiply(
	T const _s,
	fcppt::math::matrix::object<
		T,
		N,
		N,
		S
	> const &_matrix
)
{
	return
		fcppt::math::matrix::exponential_pade(
			_s
			*
			sge::camera::tracking::alexa::logarithm(
				_matrix
			)
		);
}

}

#endif
