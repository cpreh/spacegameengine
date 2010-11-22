#ifndef SGE_CAMERA_GIZMO_TO_ROTATION_MATRIX_HPP_INCLUDED
#define SGE_CAMERA_GIZMO_TO_ROTATION_MATRIX_HPP_INCLUDED

#include <sge/camera/gizmo/basic.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

namespace sge
{
namespace camera
{
namespace gizmo
{
// Note that this is not called to_rotation_matrix4 for a reason: The
// fcppt rotation matrices are 4x4 by default
template<typename T>
typename
fcppt::math::matrix::static_<T,4,4>::type const
to_rotation_matrix(
	basic<T,3> const &b)
{
	typedef
	T
	scalar;

	typedef typename
	basic<T,3>::array_type
	array_type;

	scalar const 
		zero = 
			static_cast<scalar>(0),
		one = 
			static_cast<scalar>(1);

	array_type const &a = 
		b.array();

	return 
		// NOTE that transposing here is correct!
		typename fcppt::math::matrix::static_<scalar,4,4>::type(
			a[0][0],a[0][1],a[0][2],zero,
			a[1][0],a[1][1],a[1][2],zero,
			a[2][0],a[2][1],a[2][2],zero,
			zero,zero,zero,one);
}
}
}
}

#endif
