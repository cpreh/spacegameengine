#include "../motion_state.hpp"
#include "../convert/to_bullet.hpp"
#include "../convert/point_to_sge.hpp"
#include "../body.hpp"
#include "../log.hpp"
#include <sge/collision/satellite.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <BulletDynamics/Dynamics/btRigidBody.h>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("motion_state")));
}

sge::bullet::motion_state::motion_state(
	collision::satellite &_satellite,
	btRigidBody &_body,
	point &_relative_position)
:
	satellite_(
		_satellite),
	body_(
		_body),
	relative_position_(
		_relative_position),
	position_(
		relative_position_),
	meta_body_(
		0),
	is_position_changer_(
		false)
{
	FCPPT_ASSERT(
		!body_.getMotionState());
	body_.setMotionState(
		this);
	// send an initial position change
	satellite_.position_change(
		position_);
}

void 
sge::bullet::motion_state::getWorldTransform(
	btTransform &t) const
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Bullet body requests world transformation, returning: ")
			<< position_);
	t.setOrigin(
		convert::to_bullet(
			position_));
}

void 
sge::bullet::motion_state::setWorldTransform(
	btTransform const &t)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Bullet sets world transform to: ")
			<< 
				convert::point_to_sge(
					t.getOrigin()));
					
	point const &new_position = 
		convert::point_to_sge(
			t.getOrigin());
			
	// why this? Well, the metabody (the parent body) contains multiple bodys, all of them changing their positions
	// if linear_velocity is != 0. The metabody, however, also has a position attribute, so which of his children should
	// update the parent body's position? That's the one with the position changer attribute
	if (!is_position_changer_)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("Shape is not position changer, so just assigning new position"));
		position_  = new_position;
		return;
	}
	
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Shape is position changer, old body position ")
			<< position_
			<< FCPPT_TEXT(", new body position: "));
			
	FCPPT_ASSERT(
		meta_body_);

	meta_body_->position(
		position_ - relative_position_);
		
	position_ = 
		new_position;
		
	satellite_.position_change(
		fcppt::math::vector::structure_cast<collision::point>(
			position_));
}

sge::bullet::point const 
sge::bullet::motion_state::position() const
{
	return position_;
}

void
sge::bullet::motion_state::position(
	point const &_position)
{
	position_ = 
		_position;
	// bullet doesn't notice the position has changed until we reset its motion state (kind of a hack)
	body_.setMotionState(
		this);
	satellite_.position_change(
		fcppt::math::vector::structure_cast<collision::point>(
			position_));
}

void 
sge::bullet::motion_state::meta_body(
	body &_meta_body)
{
	meta_body_ = 
		&_meta_body;
}

void
sge::bullet::motion_state::is_position_changer(
	bool const _is_position_changer)
{
	FCPPT_ASSERT(
		!_is_position_changer || meta_body_);
	is_position_changer_ = 
		_is_position_changer;
}

bool
sge::bullet::motion_state::is_position_changer() const
{
	return 
		is_position_changer_;
}

sge::bullet::motion_state::~motion_state()
{
	body_.setMotionState(
		0);
}
