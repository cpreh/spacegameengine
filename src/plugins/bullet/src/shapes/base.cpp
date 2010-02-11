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
#include <fcppt/assert_message.hpp>
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
		FCPPT_TEXT("shapes_base")));
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
	body_connection_(),
	in_world_(
		false),
	queued_group_(
		static_cast<group_id>(
			0)),
	queued_mask_(
		static_cast<group_id>(
			0))
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("created shape ")
			<< &body_);
			
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

	world_.queue_add_shape(
		*this);
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
	if (body_connection_)
		throw collision::shape_ambiguity();

	body_connection_.reset(
		new shape_body_connection(
			*this,
			_meta_body));
	
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
	body_.activate(
		true);

	// the position is now relative to the meta body
	meta_body_position(
		_meta_body.position());
	linear_velocity(
		_meta_body.linear_velocity());
}

bool
sge::bullet::shapes::base::has_meta_body() const
{
	return 
		body_connection_;
}

sge::collision::body *
sge::bullet::shapes::base::parent_body()
{
	return 
		&(body_connection_->body());
}

sge::bullet::body &
sge::bullet::shapes::base::meta_body() const
{
	return 
		body_connection_->body();
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
	/*
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("setting shape's absolute position to ")
			<< (_position + relative_position_));
	*/
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("meta_body_position ") 
			<< _position
			<< FCPPT_TEXT(" relative position ")
			<< relative_position_
			<< FCPPT_TEXT(" ")
			<< &body_);
			
	if (in_world_)
		world_.reset_shape(
			*this);

	motion_state_.position(
		_position + relative_position_);
}

void
sge::bullet::shapes::base::linear_velocity(
	point const &_linear_velocity)
{
	/*
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("setting shape's linear velocity to ")
			<< _linear_velocity);
			*/
			
	// setLinearVelocity is just an operator= call, it doesn't reactivate the body - sadly
	body_.activate(
		true);
	//body_.setActivationState(
	//	ACTIVE_TAG);
	body_.setLinearVelocity(
		convert::to_bullet(
		/*
			point(
				_linear_velocity.x()/2,
				_linear_velocity.y()/2,
				_linear_velocity.z()/2)*/_linear_velocity));
	
	satellite_->velocity_change(
		convert::point_to_sge(
			body_.getLinearVelocity()));
}

void
sge::bullet::shapes::base::velocity_change()
{
	meta_body().linear_velocity(
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
	if (!in_world_)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ 
				<< FCPPT_TEXT("shape -> group, current category is ")
				<< queued_group_
				<< FCPPT_TEXT(" and collides is ")
				<< queued_mask_
				<< FCPPT_TEXT(", group's category/collides: ")
				<< g.category()
				<< FCPPT_TEXT("/")
				<< g.collides());

		queued_group_ |= 
			g.category();
		queued_mask_ |=
			g.collides();
	}
	else
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
}

bool
sge::bullet::shapes::base::is_solid() const
{
	return 
		!(body_.getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void
sge::bullet::shapes::base::insert_into_world()
{
	FCPPT_ASSERT(
		!in_world_);
	
	world_.add_shape(
		body_);
	
	FCPPT_ASSERT(
		body_.getBroadphaseProxy());
	
	btBroadphaseProxy &p = 
		*body_.getBroadphaseProxy();
			
	p.m_collisionFilterGroup = 
		queued_group_;
	p.m_collisionFilterMask = 
		queued_mask_;
	
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Added a shape to the world, position is: ")
			<< motion_state_.position());

	in_world_ = 
		true;
}

void
sge::bullet::shapes::base::remove_from_world()
{
	FCPPT_ASSERT(
		in_world_);
		
	FCPPT_ASSERT_MESSAGE(
		!world_.in_simulation(),
		FCPPT_TEXT("You tried to remove a shape (from the world) while you are in a world::update. That's not possible!"));
		
	in_world_ = 
		false;

	FCPPT_ASSERT(
		body_.getBroadphaseProxy());
			
	btBroadphaseProxy &p = 
		*body_.getBroadphaseProxy();
			
	queued_group_ = 
		p.m_collisionFilterGroup;
	queued_mask_ = 
		p.m_collisionFilterMask;
	
	world_.remove_shape_from_world(
		body_,
		*this);
}

sge::bullet::shapes::base::~base()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("In shape destructor, shape ") 
			<< this);
			
	if (in_world_)
	{
		FCPPT_ASSERT_MESSAGE(
			!world_.in_simulation(),
			FCPPT_TEXT("You tried to remove a shape while you are in a world::update. That's not possible!"));
	}
	
	world_.remove_shape_entirely(
		body_,
		*this);
}
