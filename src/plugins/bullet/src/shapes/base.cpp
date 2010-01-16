#include "../../shapes/base.hpp"
#include "../../convert/to_bullet.hpp"
#include "../../convert/point_to_sge.hpp"
#include "../../world.hpp"
#include "../../body.hpp"
#include "../../log.hpp"
#include "../../group.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/collision/shape_ambiguity.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>

namespace
{
btRigidBody::btRigidBodyConstructionInfo const 
create_construction_info(
	btCollisionShape &_shape)
{
	return 
		btRigidBody::btRigidBodyConstructionInfo(
			static_cast<btScalar>(
				0),
			0,
			&_shape);
}

fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("shapes: base")));
}

sge::bullet::shapes::base::base(
	bullet_shape_ptr _shape,
	collision::satellite_ptr _satellite,
	collision::constraint::type const _constraint,
	bullet::world &_world,
	collision::point const &_relative_position,
	collision::solidity::type const _s)
:
	shape_(
		_shape),
	satellite_(
		_satellite),
	world_(
		_world),
	body_(
		create_construction_info(
			*shape_)),
	relative_position_(
		fcppt::math::vector::structure_cast<point>(
			_relative_position)),
	motion_state_(
		*satellite_,
		body_,
		relative_position_),
	meta_body_(
		0)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("created a shape at relative position ")
			<< _relative_position);
			
	body_.setUserPointer(
		this);
		
	switch (_s)
	{
		case collision::solidity::solid:
		break;
		case collision::solidity::nonsolid:
			body_.setCollisionFlags(
				body_.getCollisionFlags() | 
				btCollisionObject::CF_NO_CONTACT_RESPONSE);
		break;
	}
	
	body_.setCollisionFlags(
		body_.getCollisionFlags() | 
		btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	
	switch (_constraint)
	{
		case collision::constraint::no_constraint:
		break;
		case collision::constraint::constrain_2d:
			body_.setLinearFactor(
				btVector3(
					static_cast<btScalar>(
						1),
					static_cast<btScalar>(
						1),
					static_cast<btScalar>(
						0)));
			body_.setAngularFactor(
				convert::to_bullet(
					point::null()));
		break;
	}

	// NOTE: the order is important here. getBroadPhaseProxy works only if
	// the body is registered in the world
	world_.add_shape(
		body_);
	
	body_.getBroadphaseProxy()->m_collisionFilterGroup = 
	body_.getBroadphaseProxy()->m_collisionFilterMask = 
		static_cast<group_id>(
			0);
}

void
sge::bullet::shapes::base::is_position_changer(
	bool const _is_position_changer)
{
	motion_state_.is_position_changer(
		_is_position_changer);
}

bool
sge::bullet::shapes::base::is_position_changer() const
{
	return 
		motion_state_.is_position_changer();
}

void
sge::bullet::shapes::base::meta_body(
	body &_meta_body)
{
	if (has_meta_body())
		throw collision::shape_ambiguity();
	
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("a meta body was assigned to a shape"));
	
	meta_body_ = 
		&_meta_body;
	
	// since now the shape (or body) isn't static anymore, don't set the mass to zero (1 is arbitrary)
	btScalar const mass = 
		static_cast<btScalar>(
			1);
	
	btVector3 local_inertia = 
		convert::to_bullet(
			point::null());
		
	// NOTE: the inertia is bigger if the shape is bigger! Maybe we want that?
	/*
	shape_->calculateLocalInertia(
		mass,
		local_inertia);
		*/

	body_.setMassProps(
		mass,
		local_inertia);
		
	// this is done in the constructor as well, so just do it here (technically a bug, again)
	body_.updateInertiaTensor();
	
	motion_state_.meta_body(
		_meta_body);
	
	// Why this? Well, if the body was static before, it got the ISLAND_SLEEPING tag. Now it's
	// not static anymore, but bullet has a bug: It doesn't (re)set the activation state of new bodys if
	// they happen to be non-static. So we do this here
	body_.setActivationState(
		ACTIVE_TAG);
		
	// NOTE: we have to reset the group settings here because world::reset_shapes creates new broadphase proxies
	group_id const 
		group = body_.getBroadphaseProxy()->m_collisionFilterGroup,
		mask = body_.getBroadphaseProxy()->m_collisionFilterMask;
		
	world_.reset_shape(
		body_);
	
	body_.getBroadphaseProxy()->m_collisionFilterGroup = 
		group;
	body_.getBroadphaseProxy()->m_collisionFilterMask = 
		mask;
	
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("setting shape's absolute position to ")
			<< (_meta_body.position() + relative_position_));
		
	// the position is now relative to the meta body
	motion_state_.position(
		_meta_body.position() + relative_position_);
		
	linear_velocity(
		meta_body_->linear_velocity());
}

bool
sge::bullet::shapes::base::has_meta_body() const
{
	return 
		meta_body_;
}

sge::collision::body *
sge::bullet::shapes::base::parent_body()
{
	return 
		meta_body_;
}

sge::bullet::body &
sge::bullet::shapes::base::meta_body() const
{
	return 
		*meta_body_;
}

sge::collision::satellite &
sge::bullet::shapes::base::satellite() 
{
	return 
		*satellite_;
}

sge::collision::satellite const &
sge::bullet::shapes::base::satellite() const
{
	return 
		*satellite_;
}

void
sge::bullet::shapes::base::meta_body_position(
	point const &_position)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("setting shape's absolute position to ")
			<< (_position + relative_position_));
		
	motion_state_.position(
		_position + relative_position_);
}

void
sge::bullet::shapes::base::linear_velocity(
	point const &_linear_velocity)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("setting shape's linear velocity to ")
			<< _linear_velocity);
			
	body_.setLinearVelocity(
		convert::to_bullet(
			_linear_velocity));
	
	velocity_change();
}

void
sge::bullet::shapes::base::velocity_change()
{
	satellite_->velocity_change(
		convert::point_to_sge(
			body_.getLinearVelocity()));
}

sge::bullet::world &
sge::bullet::shapes::base::world() const
{
	return 
		world_;
}

void
sge::bullet::shapes::base::add_to_group(
	group &g)
{
	FCPPT_ASSERT(
		body_.getBroadphaseProxy());
		
	btBroadphaseProxy &p = 
		*body_.getBroadphaseProxy();
		
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("shape -> group, current category is ")
			<< p.m_collisionFilterGroup
			<< FCPPT_TEXT(" and collides is ")
			<< p.m_collisionFilterMask
			<< FCPPT_TEXT(", group's category/collides: ")
			<< g.category()
			<< FCPPT_TEXT("/")
			<< g.collides());
			
	p.m_collisionFilterGroup |= 
		g.category();
	p.m_collisionFilterMask |= 
		g.collides();
}

bool
sge::bullet::shapes::base::is_solid() const
{
	return 
		!(body_.getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

sge::bullet::shapes::base::~base()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("In shape destructor"));
	if (meta_body_)
		meta_body_->remove_shape(
			*this);
	world_.remove_shape(
		body_,
		*this);
}
