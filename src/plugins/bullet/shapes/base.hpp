#ifndef SGE_BULLET_SHAPES_BASE_HPP_INCLUDED
#define SGE_BULLET_SHAPES_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "../body_fwd.hpp"
#include "../world_fwd.hpp"
#include "../group_fwd.hpp"
#include "../motion_state.hpp"
#include "../bullet_shape_ptr.hpp"
#include <sge/collision/point.hpp>
#include <sge/collision/solidity.hpp>
#include <sge/collision/constraint.hpp>
#include <sge/collision/shapes/base.hpp>
#include <sge/collision/satellite_ptr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
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
	public virtual sge::collision::shapes::base
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
	
	// NOTE: this will fail if there _is_ no meta body
	body &
	meta_body() const;
	
	// Thte broadphase collision needs this
	collision::satellite &
	satellite();
	
	collision::satellite const &
	satellite() const;
	
	// this is called when the meta body's position changes, we have
	// to update our own position to be relative to this position
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
	
	~base();
protected:
	// could also be a getter function, but for this minimal case, just make the variable protected
	bullet_shape_ptr shape_;
private:
	collision::satellite_ptr satellite_;
	sge::bullet::world &world_;
	btRigidBody body_;
	point relative_position_;
	motion_state motion_state_;
	body *meta_body_;
};
}
}
}

#endif
