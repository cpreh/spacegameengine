#ifndef SGE_MATH_MACHINE_EPSILON_HPP_INCLUDED
#define SGE_MATH_MACHINE_EPSILON_HPP_INCLUDED

#include <limits>

namespace sge
{
namespace math
{
template<typename T>
struct machine_epsilon
{
	static T
	value()
	{
		return std::numeric_limits<T>::epsilon();
	}
};
}
}

#endif
