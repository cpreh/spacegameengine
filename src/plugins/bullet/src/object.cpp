#include "../object.hpp"
#include "../motion_state.hpp"
#include "../system.hpp"
#include "../conversion.hpp"
#include <sge/collision/sattelite.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <boost/bind.hpp>

sge::bullet::object::object(
	system &sys,
	collision::sattelite_ptr _sat,
	shape_ptr _shape,
	unit const _mass)
:
	sat(_sat),
	world_(sys.world()),
	shape_(_shape),
	motion_state_(
		boost::bind(&object::position_changed,this,_1)),
	body_(
		btRigidBody::btRigidBodyConstructionInfo(
			static_cast<unit>(_mass),
			&motion_state_,
			shape_.get())),
	constraint_(
		world_,
		body_,
		sys.zero_body())
{
	body_.setUserPointer(sat.get());
	world_.addRigidBody(&body_);
}
	  
void sge::bullet::object::pos(collision::point const &p)
{
	motion_state_.pos(sge_to_bullet(p));
	// TODO: this is a hack so bullet reset it's internal position. maybe we find
	// something better here
	body_.setMotionState(&motion_state_);
}

sge::collision::point const sge::bullet::object::pos() const
{
	return bullet_to_sge(motion_state_.pos());
}

void sge::bullet::object::speed(collision::point const &v)
{
	body_.setLinearVelocity(sge_to_bullet(v));
	body_.setActivationState(DISABLE_DEACTIVATION);
}

sge::collision::point const sge::bullet::object::speed() const
{
	return bullet_to_sge(body_.getLinearVelocity());
}

sge::bullet::object::~object()
{
	world_.removeRigidBody(&body_);
}

void sge::bullet::object::position_changed(point const &p)
{
	sat->position_change(bullet_to_sge(p));
}
