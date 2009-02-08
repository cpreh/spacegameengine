#ifndef SGE_GUI_UTILITY_MAX_DIM_HPP_INCLUDED
#define SGE_GUI_UTILITY_MAX_DIM_HPP_INCLUDED
 
#include <sge/math/dim/static.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <limits>
 
namespace sge
{
namespace gui
{
namespace utility
{
template<
	typename T
>
inline typename math::dim::static_<T,2>::type const
max_dim()
{
	return typename math::dim::static_<T,2>::type(
		std::numeric_limits<T>::max(),
		std::numeric_limits<T>::max());
}
}
}
}

#endif
