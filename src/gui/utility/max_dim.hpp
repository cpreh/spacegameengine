#ifndef SGE_GUI_UTILITY_MAX_DIM_HPP_INCLUDED
#define SGE_GUI_UTILITY_MAX_DIM_HPP_INCLUDED
 
#include <sge/math/dim.hpp>
#include <limits>
 
namespace sge
{
namespace gui
{
namespace utility
{
template<typename T>
inline math::dim<T,2> const max_dim()
{
	return math::dim<T,2>(
		std::numeric_limits<T>::max(),
		std::numeric_limits<T>::max());
}
}
}
}

#endif
