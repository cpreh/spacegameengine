#ifndef SGE_MATH_POINT_ROTATE_HPP_INCLUDED
#define SGE_MATH_POINT_ROTATE_HPP_INCLUDED

#include "vector.hpp"
#include "../su.hpp"
#include "../export.hpp"

namespace sge
{
namespace math
{

SGE_SYMBOL vector2 const point_rotate(
	vector2 const &point,
	vector2 const &around,
	space_unit rot);

}
}

#endif
