#ifndef SGE_COLLISION_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_COLLISION_OBJECTS_CIRCLE_HPP_INCLUDED

#include <sge/collision/objects/circle_fwd.hpp>
#include <sge/collision/point.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace collision
{
namespace objects
{
class SGE_CLASS_SYMBOL circle
{
	SGE_NONCOPYABLE(circle)
protected:
	SGE_SYMBOL circle();
public:
	virtual void center(point const &) = 0;
	virtual point const center() const = 0;
	virtual void speed(point const &) = 0;
	virtual point const speed() const = 0;
	SGE_SYMBOL virtual ~circle();
};
}
}
}

#endif
