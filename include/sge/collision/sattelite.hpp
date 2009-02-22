#ifndef SGE_COLLISION_SATTELITE_HPP_INCLUDED
#define SGE_COLLISION_SATTELITE_HPP_INCLUDED

#include <sge/collision/sattelite_fwd.hpp>
#include <sge/collision/point.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL sattelite 
{
	SGE_NONCOPYABLE(sattelite)
protected:
	SGE_SYMBOL sattelite();
public:
	virtual void position_change(point const &) = 0;
	SGE_SYMBOL virtual ~sattelite();
};
}
}

#endif
