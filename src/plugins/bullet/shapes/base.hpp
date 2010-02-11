#ifndef SGE_BULLET_SHAPES_BASE_HPP_INCLUDED
#define SGE_BULLET_SHAPES_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "../shape_body_connection.hpp"
#include "../body_fwd.hpp"
#include "../world_fwd.hpp"
#include "../group_fwd.hpp"
#include "../group_id.hpp"
#include "../bullet_shape_ptr.hpp"
#include "../point.hpp"
#include <sge/collision/point.hpp>
#include <sge/collision/solidity.hpp>
#include <sge/collision/constraint.hpp>
#include <sge/collision/shapes/base.hpp>
#include <sge/collision/satellite_ptr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <BulletDynamics/Dynamics/btRigidBody.h>

class btCollisionShape;

namespace sge
{
namespace bullet
{
namespace shapes
{
class base
:
	public virtual sge::collision::shapes::base,
	public btMotionState
{
public:
	base(
		bullet_shape_ptr,
		collision::satellite_ptr,
		collision::constraint::type,
		sge::bullet::world &,
		collision::point const &,
		collision::solidity::type);
	
	void
	is_position_changer(
		bool);
	
	bool
	is_position_changer() const;
	
	void
	meta_body(
		body &);

	bool 
	has_meta_body() const;
	
	// @override
	collision::body *
	parent_body();
	
	/// NOTE: this will fail if there _is_ no meta body
	body &
	meta_body() const;
	
	// Thte broadphase collision needs this
	collision::satellite &
	satellite();
	
	collision::satellite const &
	satellite() const;
	
	/// this is called when the meta body's position changes, we have
	/// to update our own position to be relative to this position
	void 
	meta_body_position(
		point const &);
		
	void
	linear_velocity(
		point const &);
	
	// the global collision begin/end callbacks need this
	sge::bullet::world &
	world() const;
	
	void 
	add_to_group(
		group &);

	bool 
	is_solid() const;
	
	void
	velocity_change();
	
	/// Finally, insert into world (@see in_world_)
	void
	insert_into_world();

	/// Remove the shape from the world, saving the neccesary data
	void
	remove_from_world();
	
	/// @override
	void 
	getWorldTransform(
		btTransform&) const;

	/// @override
	void 
	setWorldTransform(
		btTransform const &);
	
	~base();
protected:
	// could also be a getter function, but for this minimal case, just make the variable protected
	bullet_shape_ptr shape_;
private:
	collision::satellite_ptr satellite_;
	sge::bullet::world &world_;
	btRigidBody body_;
	point relative_position_,position_;
	bool is_position_changer_;
	fcppt::scoped_ptr<shape_body_connection> body_connection_;
	// This stores if the body has been inserted into the world yet. We have to delay insertion into the world
	// because you cannot insert bodies into the world inside the stepSimulation loop.
	bool in_world_;
	group_id queued_group_,queued_mask_;
};
}
}
}

#endif
