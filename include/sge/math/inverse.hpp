#ifndef SGE_MATH_INVERSE_HPP_INCLUDED
#define SGE_MATH_INVERSE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace sge
{
namespace math
{
template<typename T>
typename
boost::disable_if
<
	boost::is_integral<T>,
	T
>::type
inverse(
	T const t)
{
	return
		static_cast<T>(1)/t;
}
}
}

#endif