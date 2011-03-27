#ifndef SGE_PROJECTILE_DETAIL_TRIANGLE_SET_HASH_HPP_INCLUDED
#define SGE_PROJECTILE_DETAIL_TRIANGLE_SET_HASH_HPP_INCLUDED

#include <sge/projectile/triangle.hpp>
#include <boost/foreach.hpp>
#include <boost/functional/hash/hash.hpp>
#include <cstddef>

namespace sge
{
namespace projectile
{
namespace detail
{
class triangle_set_hash
{
public:
	std::size_t
	operator()(
		triangle const &s) const
	{
		std::size_t result = 0;
		BOOST_FOREACH(
			triangle::const_reference point,
			s)
		{
			BOOST_FOREACH(
				triangle::value_type::const_reference point_component,
				point)
			{
				result ^= 
					boost::hash_value(point_component) + 0x9e3779b9 + (result<<6) + (result>>2);
			}
		}
		return result;
	}
};
}
}
}

#endif
