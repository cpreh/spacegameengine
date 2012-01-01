/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <sge/src/projectile/bullet_to_vector2.hpp>
#include <sge/src/projectile/declare_local_logger.hpp>
#include <sge/src/projectile/object_extrusion_depth.hpp>
#include <sge/src/projectile/vector2_to_bullet.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <fcppt/config/external_end.hpp>


SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("ghost"))

sge::projectile::ghost::object::object(
	parameters const &p)
:
	body_enter_(),
	body_exit_(),
	box_shape_(
		// The box shape gets _HALF EXTENTS_
		fcppt::make_unique_ptr<btBoxShape>(
			btVector3(
				p.size().get().w()/2,
				p.size().get().h()/2,
				object_extrusion_depth()))),
	ghost_object_(
		fcppt::make_unique_ptr<btPairCachingGhostObject>())
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< this
			<< FCPPT_TEXT(": Created a new ghost, position ")
			<< p.position().get()
			<< FCPPT_TEXT(", size ")
			<< p.size().get());

	ghost_object_->setCollisionFlags(
		ghost_object_->getCollisionFlags() |
		btCollisionObject::CF_NO_CONTACT_RESPONSE);

	ghost_object_->setUserPointer(
		this);

	ghost_object_->setCollisionShape(
		box_shape_.get());

	position(
		p.position().get());
}

sge::projectile::vector2 const
sge::projectile::ghost::object::position() const
{
	return
		bullet_to_vector2(
			ghost_object_->getWorldTransform().getOrigin());
}

void
sge::projectile::ghost::object::position(
	vector2 const &p)
{
	ghost_object_->setWorldTransform(
		btTransform(
			btMatrix3x3::getIdentity(),
			vector2_to_bullet(
				p)));
}

fcppt::signal::auto_connection
sge::projectile::ghost::object::body_enter(
	sge::projectile::ghost::body_enter const &f)
{
	return
		body_enter_.connect(
			f);
}

fcppt::signal::auto_connection
sge::projectile::ghost::object::body_exit(
	sge::projectile::ghost::body_exit const &f)
{
	return
		body_exit_.connect(
			f);
}

sge::projectile::ghost::object::~object()
{
}

void
sge::projectile::ghost::object::enter_internal(
	body::object const &b)
{
	body_enter_(
		b);
}

void
sge::projectile::ghost::object::exit_internal(
	body::object const &b)
{
	body_exit_(
		b);
}
