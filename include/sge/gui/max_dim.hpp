#ifndef SGE_MATH_MAX_DIM_HPP_INCLUDED
#define SGE_MATH_MAX_DIM_HPP_INCLUDED

#include "../math/dim.hpp"
#include <limits>

namespace sge
{
namespace math
{
template<typename T>
inline basic_dim<T,2> const max_dim()
{
	return basic_dim<T,2>(
		std::numeric_limits<T>::max(),
		std::numeric_limits<T>::max()
	);
}
}
}

#endif
