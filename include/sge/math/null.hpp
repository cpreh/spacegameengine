#ifndef SGE_MATH_NULL_HPP_INCLUDED
#define SGE_MATH_NULL_HPP_INCLUDED

namespace sge
{
namespace math
{
template<typename T>
T null()
{
	return static_cast<T>(0);
}
}
}

#endif
