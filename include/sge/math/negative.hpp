#ifndef SGE_MATH_NEGATIVE_HPP_INCLUDED
#define SGE_MATH_NEGATIVE_HPP_INCLUDED

#include <sge/math/null.hpp>

namespace sge
{
namespace math
{
template<typename T>
bool negative(T const &t)
{
	return t < null<T>();
}
}
}

#endif
