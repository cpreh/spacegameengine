#ifndef SGE_MATH_MAX_RECT_HPP_INCLUDED
#define SGE_MATH_MAX_RECT_HPP_INCLUDED

#include "../math/rect.hpp"
#include "../math/rect_impl.hpp"
#include <limits>

namespace sge
{
namespace math
{
template<typename T>
inline basic_rect<T> const max_rect()
{
	return basic_rect<T>(
		std::numeric_limits<T>::min(),
		std::numeric_limits<T>::min(),
		std::numeric_limits<T>::max(),
		std::numeric_limits<T>::max()
	);
}
}
}

#endif
