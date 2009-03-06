#ifndef SGE_COLLISION_WORLD_HPP_INCLUDED
#define SGE_COLLISION_WORLD_HPP_INCLUDED

#include <sge/collision/world_fwd.hpp>
#include <sge/collision/unit.hpp>
#include <sge/collision/point.hpp>
#include <sge/collision/callbacks.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <sge/collision/objects/circle_fwd.hpp>
#include <sge/time/funit.hpp>
#include <sge/signals/connection.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL world
{
	SGE_NONCOPYABLE(world)
protected:
	SGE_SYMBOL world();
public:
	virtual void
	test_callback(
		::sge::collision::test_callback const &) = 0;

	virtual signals::connection const 
	register_callback(
		callback const &) = 0;
	
	virtual objects::circle_ptr const
	create_circle(
		satellite_ptr,
		point const &center,
		point const &speed,
		unit radius) = 0;

	virtual void
	update(
		time::funit delta) = 0;
	
	SGE_SYMBOL virtual ~world();
};
}
}

#endif
