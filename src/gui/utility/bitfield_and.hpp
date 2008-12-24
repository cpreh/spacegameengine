#ifndef SGE_GUI_UTILITY_BITFIELD_AND_HPP_INCLUDED
#define SGE_GUI_UTILITY_BITFIELD_AND_HPP_INCLUDED

#include <boost/foreach.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
template<typename T>
bool bitfield_and(T const &a,T const &b)
{
	T const result = a & b;
	BOOST_FOREACH(typename T::value_type const v,result)
	{
		if (v)
			return true;
	}
	return false;
}
}
}
}

#endif
