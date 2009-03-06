#ifndef SGE_COLLISION_SATELLITE_HPP_INCLUDED
#define SGE_COLLISION_SATELLITE_HPP_INCLUDED

#include <sge/collision/sattelite_fwd.hpp>
#include <sge/collision/point.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL satellite 
{
	SGE_NONCOPYABLE(satellite)
protected:
	SGE_SYMBOL satellite();
public:
	virtual void position_change(point const &) = 0;
	SGE_SYMBOL virtual ~satellite();
};
}
}

#endif
