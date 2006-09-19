#ifndef SGE_MATH_TYPES_HPP_INCLUDED
#define SGE_MATH_TYPES_HPP_INCLUDED

#include "../main/types.hpp"
#include "./vector2.hpp"
#include "./dim.hpp"
#include "./rect.hpp"

namespace sge
{

typedef vector2<space_unit> point;
typedef basic_dim<space_unit> dim;
typedef basic_rect<space_unit> rect;

const double PI = 3.14159265358979323846;

}

#endif
