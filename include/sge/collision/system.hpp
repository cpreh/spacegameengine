#ifndef SGE_COLLISION_SYSTEM_HPP_INCLUDED
#define SGE_COLLISION_SYSTEM_HPP_INCLUDED

#include <sge/collision/system_fwd.hpp>
#include <sge/collision/unit.hpp>
#include <sge/collision/callbacks.hpp>
#include <sge/collision/sattelite_fwd.hpp>
#include <sge/collision/objects/circle_fwd.hpp>
#include <sge/time/funit.hpp>
#include <sge/signals/connection.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL system
{
	SGE_NONCOPYABLE(system)
protected:
	SGE_SYMBOL system();
public:
	virtual void
	test_callback(
		::sge::collision::test_callback const &) = 0;

	virtual signals::connection const 
	register_callback(
		callback const &) = 0;
	
	virtual objects::circle_ptr const
	create_circle(
		sattelite_ptr,unit radius) = 0;

	virtual void
	update(
		time::funit delta) = 0;
	
	SGE_SYMBOL virtual ~system();
};
}
}

#endif
