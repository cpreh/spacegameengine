#include <sge/math/point_rotate.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/math/matrix_util.hpp>

sge::math::vector2 const
sge::math::point_rotate(
	vector2 const &point,
	vector2 const &around,
	space_unit const rot)
{
	return (matrix_rotation_2d(rot) * (point - around)) + around;
}
