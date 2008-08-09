#ifndef SGE_MATH_POINT_ROTATE_HPP_INCLUDED
#define SGE_MATH_POINT_ROTATE_HPP_INCLUDED

#include "vector.hpp"
#include "matrix_util.hpp"
#include "../su.hpp"
#include <cmath>

namespace sge
{
namespace math
{
/**
 * Rotates a point around another point at angle \c rot
 */
vector2 point_rotate(const vector2 &point,const vector2 &around,const space_unit rot);
}
}

#endif
