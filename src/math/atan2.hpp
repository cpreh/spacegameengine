#ifndef SGE_MATH_ATAN2_HPP_INCLUDED
#define SGE_MATH_ATAN2_HPP_INCLUDED

#include "vector.hpp"

#include <cmath>

namespace sge
{
namespace math
{
template<typename T>
inline T atan2(const sge::math::basic_vector<T,2> &v)
{
	return std::atan2(v.y(),v.x());
}
}
}

#endif
