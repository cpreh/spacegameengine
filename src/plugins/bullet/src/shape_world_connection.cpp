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


#include "../shape_world_connection.hpp"
#include "../world.hpp"
#include "../log.hpp"
#include "../shapes/base.hpp"
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <fcppt/assert.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/math/null.hpp>
#include <fcppt/text.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("shape_world_connection")));
}

sge::bullet::shape_world_connection::shape_world_connection(
	shapes::base &_shape,
	world &_world)
:
	shape_(
		_shape),
	world_(
		_world),
	in_world_(
		false),
	queued_mask_(
		fcppt::math::null<group_id>()),
	queued_group_(
		fcppt::math::null<group_id>())
{
}

bool
sge::bullet::shape_world_connection::in_world() const
{
	return 
		in_world_;
}

sge::bullet::group_id &
sge::bullet::shape_world_connection::mask()
{
	return 
		in_world_
			?
				shape_.bullet_body().getBroadphaseProxy()->m_collisionFilterMask
			:
				queued_mask_;
}

sge::bullet::group_id &
sge::bullet::shape_world_connection::group()
{
	return 
		in_world_
			?
				shape_.bullet_body().getBroadphaseProxy()->m_collisionFilterGroup
			:
				queued_group_;
}

void
sge::bullet::shape_world_connection::insert()
{
	FCPPT_ASSERT(
		!in_world_);
		
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< &shape_
			<< FCPPT_TEXT(": inserting..."));
	
	world_.add_shape(
		shape_);
	
	btBroadphaseProxy &p = 
		*shape_.bullet_body().getBroadphaseProxy();
			
	p.m_collisionFilterGroup = 
		queued_group_;
	p.m_collisionFilterMask = 
		queued_mask_;
	
	in_world_ = 
		true;
}

void 
sge::bullet::shape_world_connection::remove()
{
	FCPPT_ASSERT(
		in_world_);
		
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< &shape_
			<< FCPPT_TEXT(": removing..."));
		
	in_world_ = 
		false;

	btBroadphaseProxy &p = 
		*shape_.bullet_body().getBroadphaseProxy();
			
	queued_group_ = 
		p.m_collisionFilterGroup;
	queued_mask_ = 
		p.m_collisionFilterMask;
	
	world_.remove_shape_from_world(
		shape_);
}

sge::bullet::shape_world_connection::~shape_world_connection()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< &shape_
			<< FCPPT_TEXT(": in destructor."));
			
	if (in_world_)
		remove();

	world_.remove_shape_entirely(
		shape_);
}
