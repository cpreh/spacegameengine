#ifndef SGE_COLLISION_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_COLLISION_OBJECTS_CIRCLE_HPP_INCLUDED

#include "fwd.hpp"
#include "../point.hpp"
#include "../sattelite_fwd.hpp"
#include "../../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace collision
{
namespace objects
{
class SGE_CLASS_SYMBOL circle : public boost::noncopyable
{
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
