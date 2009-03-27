#ifndef SGE_COLLISION_OBJECTS_BASE_HPP_INCLUDED
#define SGE_COLLISION_OBJECTS_BASE_HPP_INCLUDED

#include <sge/collision/objects/base_fwd.hpp>
#include <sge/collision/point.hpp>

namespace sge
{
namespace collision
{
namespace objects
{
class base
{
public:
	virtual void pos(point const &) = 0;
	virtual point const pos() const = 0;
	virtual void speed(point const &) = 0;
	virtual point const speed() const = 0;
	virtual ~base();
};
}
}
}

#endif
