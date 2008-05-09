#ifndef SGE_MATH_DIFF_HPP_INCLUDED
#define SGE_MATH_DIFF_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib> // both are needed for alle overloads of std::abs

namespace sge
{
namespace math
{

template<typename T>
inline typename boost::disable_if<boost::is_unsigned<T>, T>::type
diff(T const &a, T const &b)
{
	return std::abs(a - b);
}

template<typename T>
inline typename boost::enable_if<boost::is_unsigned<T>, T>::type
diff(T const& a, T const &b)
{
	return std::min(a - b, b - a);
}

}
}

#endif
