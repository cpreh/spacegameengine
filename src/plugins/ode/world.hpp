#ifndef SGE_ODE_WORLD_HPP_INCLUDED
#define SGE_ODE_WORLD_HPP_INCLUDED

#include "transformer.hpp"
#include "point.hpp"
#include "group_id.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/optional_rect.hpp>
#include <sge/collision/callback_signal.hpp>
#include <sge/collision/dim.hpp>
#include <ode/ode.h>
#include <map>
#include <utility>

namespace sge
{
namespace ode
{
class world
:
	public sge::collision::world
{
public:
	world(
		collision::optional_rect const &);
	
	signal::auto_connection
	register_test_callback(
		collision::test_callback const &);

	void 
	test_callback_combiner(
		collision::test_callback_combiner const &);
	
	signal::auto_connection
	register_begin_callback(
		collision::callback const &);
		
	signal::auto_connection
	register_end_callback(
		collision::callback const &);
		
	collision::body_ptr const 
	create_body(
		collision::satellite_ptr,
		collision::point const &,
		collision::point const &);
	
	collision::shapes::circle_ptr const
	create_circle(
		collision::unit radius);
	
	collision::group_ptr const 
	create_group();

	void
	update(
		collision::time_unit delta);
	
	~world();
private:
	// body needs the worldid
	friend class body;
	
	typedef 
	std::map
	<
		std::pair
		<
			dBodyID,
			dBodyID
		>,
		bool
	> object_map;
	
	dWorldID const world_; 
	dSpaceID const space_;
	collision::callback_signal 
		begin_signal_,
		end_signal_;
	sge::signal::object<collision::test_callback_fn> 
		test_signal_;
	group_id group_id_;
	dReal time_remainder_;
	object_map collisions_;
	transformer transformer_;
	unsigned long body_count_;
	
	void step(
		dReal);
	void check_end_signals();
	group_id next_group_id();
	static void static_collide(
		void *,
		dGeomID,
		dGeomID);
	void collide(
		dGeomID,
		dGeomID);
	void call_signal(
		collision::callback_signal &,
		dBodyID,
		dBodyID);
	void destroy_body(
		dBodyID);
};
}
}

#endif
