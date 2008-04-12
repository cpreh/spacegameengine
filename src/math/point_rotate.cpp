#include <sge/math/point_rotate.hpp>
#include <sge/math/matrix_impl.hpp>

sge::math::vector2 sge::math::point_rotate(const vector2 &point,const vector2 &around,const space_unit rot)
{
	return (matrix_rotation_2d(rot) * (point - around)) + around;
}
