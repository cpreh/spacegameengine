#ifndef SGE_BITWISE_CAST_HPP_INCLUDED
#define SGE_BITWISE_CAST_HPP_INCLUDED

#include <cstring>
#include <boost/static_assert.hpp>

namespace sge
{
	template<typename Dest, typename Source> Dest bitwise_cast(const Source& s)
	{
		BOOST_STATIC_ASSERT(sizeof(Dest)==sizeof(Source));
		Dest d;
		std::memcpy(&d,&s,sizeof(Source));
		return d;
	}
}

#endif
