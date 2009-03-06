#ifndef SGE_ODE_WORLD_HPP_INCLUDED
#define SGE_ODE_WORLD_HPP_INCLUDED

#include "world_wrapper.hpp"
#include "space.hpp"
#include <sge/collision/world.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class world : public sge::collision::world
{
public:
	world(
		boost::optional<collision::rect> const &);

	void
	test_callback(
		::sge::collision::test_callback const &);

	signals::connection const 
	register_callback(
		collision::callback const &);
	
	collision::objects::circle_ptr const
	create_circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit radius);

	void
	update(
		time::funit delta);
private:
	world_wrapper world_;
	space space_;
	sge::collision::test_callback test_callback_;
	sge::collision::callback_signal callback_;

	static void internal_static_collide(void *,dGeomID,dGeomID);
	void internal_collide(dGeomID,dGeomID);
};
}
}

#endif
