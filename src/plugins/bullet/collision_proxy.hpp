#ifndef SGE_BULLET_COLLISION_PROXY_HPP_INCLUDED
#define SGE_BULLET_COLLISION_PROXY_HPP_INCLUDED

#include "shapes/base_fwd.hpp"
#include "world_fwd.hpp"
#include <utility>

namespace sge
{
namespace bullet
{
class collision_proxy
{
public:
	typedef 
	std::pair
	<
		shapes::base*,
		shapes::base*
	> 
	shape_pair;
	
	collision_proxy(
		shapes::base &,
		shapes::base &,
		world &);
	
	bool 
	operator<(
		collision_proxy const &) const;
	
	shape_pair const &
	shapes() const;
	
	sge::bullet::world &
	world() const;
private:
	shape_pair shapes_;
	sge::bullet::world *world_;
};
}
}

#endif