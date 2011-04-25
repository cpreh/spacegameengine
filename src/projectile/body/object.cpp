/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../declare_local_logger.hpp"
#include "../bullet_to_vector2.hpp"
#include "../vector2_to_bullet.hpp"
#include "../bullet_to_vector2.hpp"
#include "solidity/extract_mass.hpp"
#include "solidity/is_solid.hpp"
#include "detail/motion_state.hpp"
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/vector3.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <LinearMath/btMatrix3x3.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <LinearMath/btTransform.h>

SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("body"))

namespace
{
btVector3 const
inertia_for_shape(
	btCollisionShape &shape,
	sge::projectile::body::solidity::variant const &solidity)
{
	btVector3 inertia(
		0,
		0,
		0);

	btScalar const mass = 
		sge::projectile::body::solidity::extract_mass(
			solidity);

	// FIXME: Rather test if the solidity actually implies a mass, then
	// do an if() on that.
	if(mass > static_cast<btScalar>(0.000001))
	{
		FCPPT_LOG_DEBUG(
			local_log,
			fcppt::log::_ 
				<< FCPPT_TEXT("solid body with mass ") << mass << FCPPT_TEXT(" so calculating inertia"));
		shape.calculateLocalInertia(
			mass,
			inertia);
	}

	return inertia;
}

btMatrix3x3 const
create_rotation_matrix(
	btScalar const angle)
{
	btMatrix3x3 result = btMatrix3x3::getIdentity();
	result.setEulerYPR(
		0,
		0,
		angle);
	return result;
}
}

sge::projectile::body::object::object(
	parameters const &p)
:
	transformation_(
		fcppt::make_unique_ptr<btTransform>(
			create_rotation_matrix(
				p.rotation().get()),
			vector2_to_bullet(
				p.position().get()))),
	motion_state_(
		fcppt::make_unique_ptr<detail::motion_state>(
			fcppt::ref(
				*this))),
	position_change_(),
	rotation_change_(),
	shape_(
		p.shape()),
	body_(
		fcppt::make_unique_ptr<btRigidBody>(
			btRigidBody::btRigidBodyConstructionInfo(
				// mass
				solidity::extract_mass(
					p.solidity()),
				// motion state
				motion_state_.get(),
				// shape
				&(shape_->bullet_shape()),
				inertia_for_shape(
					shape_->bullet_shape(),
					p.solidity())))),
	user_data_(
		p.user_data())
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": Created a new body, position ")
			<< p.position().get()
			<< FCPPT_TEXT(", rotation ")
			<< p.rotation().get()
			<< FCPPT_TEXT(", mass ")
			<< 
				solidity::extract_mass(
					p.solidity())
			<< FCPPT_TEXT(", linear velocity ")
			<< 
				p.linear_velocity().get()
			<< FCPPT_TEXT(", angular velocity ")
			<<
				p.angular_velocity().get());

	body_->setUserPointer(
		this);

	if(!solidity::is_solid(p.solidity()))
	{
		FCPPT_LOG_DEBUG(
			local_log,
			fcppt::log::_ 
				<< this
				<< FCPPT_TEXT(": Setting to nonsolid (no contact response)"));
		body_->setCollisionFlags(
			body_->getCollisionFlags() | 
			btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	// Constrain to 2D
	body_->setLinearFactor(
		btVector3(
			static_cast<btScalar>(
				1),
			static_cast<btScalar>(
				1),
			static_cast<btScalar>(
				0)));

	linear_velocity(
		p.linear_velocity().get());

	body_->setAngularFactor(
		btVector3(
			static_cast<btScalar>(
				0),
			static_cast<btScalar>(
				0),
			static_cast<btScalar>(
				1)));

	angular_velocity(
		p.angular_velocity().get());
}

sge::projectile::vector2 const 
sge::projectile::body::object::position() const
{
	return 
		bullet_to_vector2(
			transformation_->getOrigin());
}

void 
sge::projectile::body::object::position(
	vector2 const &p)
{
	FCPPT_LOG_VERBOSE(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": Somebody reset the body's position to ") 
			<< 
				p);
	transformation_->setOrigin(
		vector2_to_bullet(
			p));
	// For speed and position calculation afterwards, it uses the
	// centerOfMassTransform and the *Interpolation* methods, so we
	// reset them here, too. It _seems_ to work at least.
	//body_->setWorldTransform(
	//	transformation_);
	body_->setCenterOfMassTransform(
		*transformation_);
	//body_->setInterpolationWorldTransform(
	//	*transformation_);
	// We have to re-activate a maybe-sleeping body
	body_->setActivationState(
		ACTIVE_TAG);
	position_change_(
		sge::projectile::body::position(
			p));
}

sge::projectile::vector2 const 
sge::projectile::body::object::linear_velocity() const
{
	return 
		bullet_to_vector2(
			body_->getLinearVelocity());
}

void 
sge::projectile::body::object::linear_velocity(
	vector2 const &v)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": Somebody reset the body's linear velocity to ") 
			<< 
				v);
	body_->setLinearVelocity(
		vector2_to_bullet(
			v));
	// We have to re-activate a maybe-sleeping body
	body_->setActivationState(
		ACTIVE_TAG);
}

sge::projectile::scalar
sge::projectile::body::object::angular_velocity() const
{
	return 
		body_->getAngularVelocity().length();
}

void 
sge::projectile::body::object::angular_velocity(
	scalar const v)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": Somebody reset the body's angular velocity to ") 
			<< 
				v);
	body_->setAngularVelocity(
		btVector3(
			0,
			0,
			v));

	// We have to re-activate a maybe-sleeping body
	body_->setActivationState(
		ACTIVE_TAG);
}

sge::projectile::shape::shared_base_ptr const
sge::projectile::body::object::shape() const
{
	return shape_;
}

sge::projectile::scalar
sge::projectile::body::object::rotation() const
{
	btScalar y,x,z;
	transformation_->getBasis().getEulerYPR(
		y,x,z);
	return 
		z;
}

void 
sge::projectile::body::object::rotation(
	scalar const r)
{
	FCPPT_LOG_VERBOSE(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": Somebody reset the body's rotation to ") 
			<< 
				r);
	transformation_->getBasis().setEulerYPR(
		0,
		0,
		r);
	body_->setWorldTransform(
		*transformation_);
	rotation_change_(
		sge::projectile::body::rotation(
			rotation()));
}

fcppt::signal::auto_connection
sge::projectile::body::object::position_change(
	sge::projectile::body::position_change const &f)
{
	return 
		position_change_.connect(
			f);
}

fcppt::signal::auto_connection
sge::projectile::body::object::rotation_change(
	sge::projectile::body::rotation_change const &f)
{
	return 
		rotation_change_.connect(
			f);
}

sge::projectile::body::user_data const &
sge::projectile::body::object::user_data() const
{
	return user_data_;
}

sge::projectile::body::object::~object()
{
}

// @override
void	
sge::projectile::body::object::getWorldTransform(
	btTransform &t) const
{
	t = *transformation_;
}

// @override
void	
sge::projectile::body::object::setWorldTransform(
	btTransform const &t)
{
	FCPPT_LOG_VERBOSE(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": Somebody wants to reset our world transformation! "));
	(*transformation_) = t;
	FCPPT_LOG_VERBOSE(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": New position ")
			<<
				this->position()
			<< FCPPT_TEXT(", rotation ")
			<<
				this->rotation());
	FCPPT_LOG_VERBOSE(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": New linear velocity ")
			<<
				this->linear_velocity());
	position_change_(
		sge::projectile::body::position(
			this->position()));
	rotation_change_(
		sge::projectile::body::rotation(
			this->rotation()));
}
