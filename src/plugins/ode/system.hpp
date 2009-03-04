#ifndef SGE_ODE_SYSTEM_HPP_INCLUDED
#define SGE_ODE_SYSTEM_HPP_INCLUDED

#include "library.hpp"
#include "world.hpp"
#include "space.hpp"
#include <sge/collision/system.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class system : public collision::system
{
public:
	system();

	void
	test_callback(
		::sge::collision::test_callback const &);

	signals::connection const 
	register_callback(
		callback const &);
	
	objects::circle_ptr const
	create_circle(
		sattelite_ptr,
		collision::point const &center,
		collision::point const &speed,
		unit radius);

	void
	update(
		time::funit delta);
private:
	library library_;
	world world_;
	space space_;
	sge::collision::test_callback test_callback_;
	sge::collision::callback_signal callback_;

	static void internal_static_collide(void *,dGeomID,dGeomID);
	void internal_collide(dGeomID,dGeomID);
};
}
}

#endif
