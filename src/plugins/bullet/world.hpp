#ifndef SGE_BULLET_WORLD_HPP_INCLUDED
#define SGE_BULLET_WORLD_HPP_INCLUDED

#include "group_id.hpp"
#include "overlap_filter.hpp"
#include "collision_proxy_fwd.hpp"
#include "body_manager.hpp"
#include "shapes/base_fwd.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/optional_box.hpp>
#include <sge/collision/constraint.hpp>
#include <fcppt/signal/auto_connection.hpp>

#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

#include <set>

class btRigidBody;

namespace sge
{
namespace bullet
{
class world
:
	public sge::collision::world
{
public:
	world(
		collision::optional_box const &,
		collision::constraint::type);
	
	fcppt::signal::auto_connection
	register_test_callback(
		collision::test_callback const &);
	
	void 
	test_callback_combiner(
		collision::test_callback_combiner const &);

	fcppt::signal::auto_connection
	register_begin_callback(
		collision::shape_callback const &);
		
	fcppt::signal::auto_connection
	register_end_callback(
		collision::shape_callback const &);
	
	fcppt::signal::auto_connection
	register_solid_callback(
		collision::shape_callback const &);
		
	collision::body_ptr const 
	create_body(
		collision::shapes::container const &,
		collision::point const &,
		collision::point const &);
	
	collision::shapes::sphere_ptr const
	create_sphere(
		collision::satellite_ptr,
		collision::unit radius,
		collision::solidity::type,
		collision::point const &);

	collision::shapes::box_ptr const
	create_box(
		collision::satellite_ptr,
		collision::dim const &,
		collision::solidity::type,
		collision::point const &);
	
	collision::group_ptr const 
	create_group();

	void
	update(
		collision::time_unit delta);
	
	void
	collides_with(
		collision::group_ptr,
		collision::group_ptr);
		
	void 
	queue_add_shape(
		shapes::base &);
	
	/// This is called from shapes::base::insert_into_world (which is queued)
	void 
	add_shape(
		btRigidBody &);
	
	/// When a shape is assigned a meta body, the bullet body switches from static to
	/// dynamic. For this to work (a bug?) we have to reinsert the shape to the world.
	/// This is also important because you cannot really reset the position of a body,
	/// you have to delete it and add it again
	void
	reset_shape(
		shapes::base &);
		
	/// This function removes a shape from the world _immediately_. This is called from
	/// a shape's destructor (where queueing the deletion is not possible). It's also called
	/// from shapes::base::remove_from_world (which is, in turn, queued).
	void 
	remove_shape(
		btRigidBody &,
		shapes::base &);
	
	// this is called by the system in the global callbacks
	collision_proxy const &
	collision_begin(
		btManifoldPoint &,
		shapes::base &,
		shapes::base &);
		
	void
	collision_end(
		shapes::base &,
		shapes::base &);
	
	void 
	solid_collision(
		shapes::base &,
		shapes::base &);
private:
	typedef 
	std::set
	<
		shapes::base*
	> 
	solid_collision_set;
	
	typedef
	std::set
	<
		shapes::base*
	> 
	queued_shapes_set;
	
	/// this is mainly for memory allocation, I think
	btDefaultCollisionConfiguration configuration_;
	/// the dispatcher gets the collision pairs from the broadphase and
	/// calls the correct pair collision function.
	btCollisionDispatcher dispatcher_;
	/// the broadphase stores the body's bounding boxes and takes care of the
	/// "rough" collision detection. The Dbvt broadphase is suited for large 
	/// environments and you don't have to specify a bounding box for the world
	btDbvtBroadphase broadphase_;
	/// NOTE: I don't know what this is for
	btSequentialImpulseConstraintSolver constraint_solver_;
	/// the world, the container of all bodys
	btDiscreteDynamicsWorld world_;
	
	collision::constraint::type constrain_;
	overlap_filter overlap_filter_;
	body_manager body_manager_;
	group_id group_id_;
	/// This stores the shapes which are solid and collided with a different solid object.
	/// We need this to emit velocity changes
	solid_collision_set solid_collisions_;
	queued_shapes_set queued_insert_shapes_;
	queued_shapes_set queued_delete_shapes_;
	
	group_id 
	next_group_id();
};
}
}

#endif
